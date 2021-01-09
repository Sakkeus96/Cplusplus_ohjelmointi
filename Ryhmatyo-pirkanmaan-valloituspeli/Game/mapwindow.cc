#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include <boost/algorithm/string.hpp>

using namespace std;

//Creates QMainWindow object, and CustomGameScene object which is the game map
MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_customscene(new CustomGameScene(this))

{
    m_ui->setupUi(this);
    CustomGameScene* sgs_rawptr = m_customscene.get();
    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    this->setWindowTitle("Pirkanmaa");
    //Creates GameEventHandler, ObjectManager and GameEngine and stores pointers
    //to them.
    std::shared_ptr<GameEventHandler> handler_pointer (new GameEventHandler());
    std::shared_ptr<ObjectManager> manager_pointer (new ObjectManager());
    std::shared_ptr<Gameengine> gameengine (new Gameengine());
    handler_ = handler_pointer;
    manager_= manager_pointer;
    gameengine_ = gameengine;
    gameengine_->setHandlerAndManager(handler_, manager_);
    gameengine_->setHeightAndWidth(m_customscene->getSize());

    connect(m_ui->endTurnButton, SIGNAL(clicked(bool)), this,
            SLOT(endTurn()));
    connect(sgs_rawptr, SIGNAL(pointGiver(QPointF)), this,
            SLOT(transferPointer(QPointF)));
    connect(m_ui->WorkerButton, SIGNAL(clicked(bool)), this,
            SLOT(workerButtonClicked()));
    connect(m_ui->MinerButton, SIGNAL(clicked(bool)), this,
            SLOT(minerButtonClicked()));
    connect(m_ui->LumberjackButton, SIGNAL(clicked(bool)), this,
            SLOT(lumberjackButtonClicked()));
    connect(m_ui->AssignCitizenButton, SIGNAL(clicked(bool)), this,
            SLOT(assingCitizenButtonClicked()));
    connect(m_ui->CancelCitizenAssigningButton, SIGNAL(clicked(bool)), this,
            SLOT(cancelCitizenAssigningButtonClicked()));
    connect(m_ui->resourceinfoButton, SIGNAL(clicked(bool)), this,
            SLOT(resourceInfoButtonClicked()));

    //Sets Winning Labels hidden
    m_ui->WinningLabel1->setVisible(false);
    m_ui->WinningLabel2->setVisible(false);
    m_ui->WinningLabel3->setVisible(false);
    m_ui->WinningWidget->setVisible(false);
    m_ui->WinningLabelYourScore->setVisible(false);
    m_ui->WinningLabelHighScoreLabel->setVisible(false);
    m_ui->WinningLabelYourScoreNumber->setVisible(false);

    //Sets texts to HighScore labels and sets them then hidden
    m_ui->HighScoreLabel1->setVisible(false);
    m_ui->HighScoreLabel1->setText(QString::fromStdString("1."));
    m_ui->HighScoreLabel2->setVisible(false);
    m_ui->HighScoreLabel2->setText(QString::fromStdString("2."));
    m_ui->HighScoreLabel3->setVisible(false);
    m_ui->HighScoreLabel3->setText(QString::fromStdString("3."));
    m_ui->HighScoreLabel4->setVisible(false);
    m_ui->HighScoreLabel4->setText(QString::fromStdString("4."));
    m_ui->HighScoreLabel5->setVisible(false);
    m_ui->HighScoreLabel5->setText(QString::fromStdString("5."));

    //Defines Color Codes in MapWindow
    m_ui->ForestColorLabel->setStyleSheet("background-color: rgb(53,120,53)");
    m_ui->GrasslandColorLabel->setStyleSheet("background-color: rgb(122,202,0)");
    m_ui->MountainColorLabel->setStyleSheet("background-color: rgb(132,132,132)");
    m_ui->IcefieldColorLabel->setStyleSheet("background-color: rgb(213,247,247)");
    m_ui->DesertColorLabel->setStyleSheet("background-color: rgb(217,193,61)");
    m_ui->SwampColorLabel->setStyleSheet("background-color: rgb(42,209,139)");

    m_ui->HeadQuartersColorLabel->setStyleSheet("background-color: rgb(250,0,0)");
    m_ui->BankColorLabel->setStyleSheet("background-color: rgb(245, 255, 48)");
    m_ui->SawmillColorLabel->setStyleSheet("background-color: rgb(150, 89, 17)");
    m_ui->OremineColorLabel->setStyleSheet("background-color: rgb(217, 188, 154)");
    m_ui->FarmColorLabel->setStyleSheet("background-color: rgb(255, 119, 0)");
    m_ui->OutpostColorLabel->setStyleSheet("background-color: rgb(23, 23, 22)");


    m_ui->BasicWorkerColorLabel->setStyleSheet("background-color: rgb(36, 42, 237)");
    m_ui->MinerColorLabel->setStyleSheet("background-color: rgb(237, 36, 217)");
    m_ui->LumberjackColorLabel->setStyleSheet("background-color: rgb(0, 255, 251)");



    //Opens dialog story
    dialogStory();

    //Opens dialog
    dialog();
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::dialog()
{
    Dialog* startdialog = new Dialog(this);
    startdialog->setModal(true);
    connect(startdialog, SIGNAL(playerSignal(int,std::vector<std::string>)), this,
            SLOT(setPlayers(int,std::vector<std::string>)));
    if (!startdialog->exec())
    {
        dialog();
    }
}

void MapWindow::setPlayers(int playercount,std::vector<std::string> players)
{
    //Creates map and add tiles to it and then draws tiles
    Course::WorldGenerator& world = Course::WorldGenerator::getInstance();
    world.addConstructor<Course::Forest>(10);
    world.addConstructor<Mountain>(5);
    world.addConstructor<Course::Grassland>(10);
    world.addConstructor<Icefield>(3);
    world.addConstructor<Swamp>(3);
    world.addConstructor<Desert>(5);
    world.generateMap(10,10,2,manager_,handler_);
    for (auto object : manager_->getTilesForMap())
    {
        MapWindow::drawItem(object);
    }

    //Creates players and updates MapWindow for first round
    gameengine_->setPlayers(players, playercount);
    QString playername = gameengine_->getPlayerName();
    QString round = gameengine_->getRound();
    m_ui->roundText->setText(round);
    m_ui->playerText->setText(playername);

    //Defines winning resources and updates Mapwindow
    Course::ResourceMap WINNER_RESOURCES = WINNING_RESOURCES;
    m_ui->winMoneyLabel->setText(QString::number(WINNER_RESOURCES[Course::MONEY]));
    m_ui->winFoodLabel->setText(QString::number(WINNER_RESOURCES[Course::FOOD]));
    m_ui->winWoodLabel->setText(QString::number(WINNER_RESOURCES[Course::WOOD]));
    m_ui->winStoneLabel->setText(QString::number(WINNER_RESOURCES[Course::STONE]));
    m_ui->winOreLabel->setText(QString::number(WINNER_RESOURCES[Course::ORE]));

    //Creates and draws HeadQuarters for players
    std::vector<std::shared_ptr<Course::HeadQuarters>> hqs = gameengine_
            ->startSetup();
    for (auto hq : hqs)
    {
        MapWindow::drawItem(hq);
    }

    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                gameengine_->getPlayerNumber());

    //Checks the availability of the first player's buildable buildings
    possibleBuildingVectorUpdater();

    //Updates the first player's resources
    updateResources(handler_->getResourceVector(player));
}

void MapWindow::endTurn()
{
    turn_end_ = false;

    //Cleares Mainwindow for next player
    m_ui->gameInfo->clear();
    clearWorkerManagement();
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                gameengine_->getPlayerNumber());

    //Updates tile production ready for current players next turn
    manager_->updateTileProduction(player);

    //Changes the round and updates Mainwindow for next player
    gameengine_->roundHandler();
    std::shared_ptr<Course::PlayerBase> new_player = handler_->getPlayer(
                gameengine_->getPlayerNumber());
    possibleBuildingVectorUpdater();
    updateResources(handler_->getResourceVector(new_player));
    QString playername = gameengine_->getPlayerName();
    QString round = gameengine_->getRound();
    m_ui->roundText->setText(round);
    m_ui->playerText->setText(playername);
    //Checks if the next player is winner and ends the game
    if(checkWin() == true)
    {   GetHighScore(new_player);
        //Updates winning widget
        m_ui->WinningWidget->setVisible(true);
        m_ui->WinningLabel2->setText(playername);
        m_ui->WinningLabel1->setVisible(true);
        m_ui->WinningLabel2->setVisible(true);
        m_ui->WinningLabel3->setVisible(true);

        m_ui->WinningLabelYourScore->setVisible(true);
        m_ui->WinningLabelHighScoreLabel->setVisible(true);
        m_ui->WinningLabelYourScoreNumber->setVisible(true);

        m_ui->HighScoreLabel1->setVisible(true);
        m_ui->HighScoreLabel2->setVisible(true);
        m_ui->HighScoreLabel3->setVisible(true);
        m_ui->HighScoreLabel4->setVisible(true);
        m_ui->HighScoreLabel5->setVisible(true);

        m_ui->WorkerButton->setEnabled(false);
        m_ui->endTurnButton->setEnabled(false);
        m_ui->MinerButton->setEnabled(false);
        m_ui->LumberjackButton->setEnabled(false);
        m_ui->CancelCitizenAssigningButton->setEnabled(false);
    }
}

void MapWindow::transferPointer(QPointF point)
{
    //If player has moves left in turn
    if(!turn_end_)
    {
        std::pair<int, std::shared_ptr<Course::TileBase>> owner = gameengine_
                ->mouseEvent(point);
        clearWorkerManagement();
        int enemy_tile = 2;

        //If player clicks own tile or no-one's tile
        if (owner.first != enemy_tile)
        {
            //Opens Dialog
            m_ui->gameInfo->clear();
            DialogTile* dialogtile = new DialogTile(this);
            dialogtile->setModal(true);
            connect(this,
                    SIGNAL(dataGiver(std::pair<int, std::shared_ptr<Course::TileBase>>,
                                     std::vector<std::string>)),
                    dialogtile,
                    SLOT(saveData(std::pair<int,std::shared_ptr<Course::TileBase>>,
                                  std::vector<std::string>)));
            connect(dialogtile,
                    SIGNAL(giveAction(std::string,std::string,std::string)),
                    this,
                    SLOT(transferDialogInformation(std::string,std::string,
                                                   std::string)));
            emit dataGiver(owner, possible_buildings_vector_);
            dialogtile->exec();
        }
        //If player clicks  enemy tile
        else
        {
            QString text = "You can not click enemy area!";
            m_ui->gameInfo->setText(text);
        }
    }
    else
    {
        m_ui->gameInfo->setText("You are out of moves!");
    }
}

void MapWindow::workerButtonClicked()
{   //Sets worker button as selected button

    m_ui->LumberjackButton->setEnabled(false);
    m_ui->MinerButton->setEnabled(false);
    m_ui->WorkerButton->setStyleSheet("background-color: red");
    m_ui->CancelCitizenAssigningButton->setEnabled(true);
    std::shared_ptr<Course::PlayerBase> current_player = handler_->
            getPlayer(gameengine_->getPlayerNumber());
    //Checks if move has already used
    if (turn_end_)
    {
        m_ui->gameInfo->setText("You are out of moves!");
    }

    //Checks if there is enough resources
    else if (handler_->checkIfEnoughResources(current_player,
                                              Course::ConstResourceMaps::
                                              BW_RECRUITMENT_COST))
    {
        m_ui->AssignCitizenButton->setEnabled(true);
    }
    else
    {
        m_ui->gameInfo->setText("You do not have enough resources!");
    }
}

void MapWindow::minerButtonClicked()
{
    //Sets miner button as selected button
    m_ui->WorkerButton->setEnabled(false);
    m_ui->LumberjackButton->setEnabled(false);
    m_ui->MinerButton->setStyleSheet("background-color: red");
    m_ui->CancelCitizenAssigningButton->setEnabled(true);
    std::shared_ptr<Course::PlayerBase> current_player = handler_->
            getPlayer(gameengine_->getPlayerNumber());

    //Checks if move has already used
    if (turn_end_)
    {
        m_ui->gameInfo->setText("You are out of moves!");
    }

    //Checks if there is enough resources
    else if (handler_->checkIfEnoughResources(current_player,
                                              MINER_RECRUITMENT_COST))
    {
        m_ui->AssignCitizenButton->setEnabled(true);
    }
    else
    {
        m_ui->gameInfo->setText("You do not have enough resources!");
    }
}

void MapWindow::lumberjackButtonClicked()
{
    //Sets lumberjack button as selected button
    m_ui->WorkerButton->setEnabled(false);
    m_ui->MinerButton->setEnabled(false);
    m_ui->LumberjackButton->setStyleSheet("background-color: red");
    m_ui->CancelCitizenAssigningButton->setEnabled(true);
    std::shared_ptr<Course::PlayerBase> current_player = handler_->
            getPlayer(gameengine_->getPlayerNumber());

    //Checks if move has already used
    if (turn_end_)
    {
        m_ui->gameInfo->setText("You are out of moves!");
    }

    //Checks if there is enough resources
    else if (handler_->checkIfEnoughResources(current_player,
                                              LUMBERJACK_RECRUITMENT_COST))
    {
        m_ui->AssignCitizenButton->setEnabled(true);
    }
    else
    {
        m_ui->gameInfo->setText("You do not have enough resources!");
    }
}

void MapWindow::resourceInfoButtonClicked()
{   //Opens resourceinfo dialog
    m_ui->gameInfo->clear();
    Dialoginfo* dialoginfo = new Dialoginfo(this);
    dialoginfo->setModal(true);
    dialoginfo->exec();
}


void MapWindow::clearWorkerManagement()
{
    //Sets Citizen Management section to its initial stage
    m_ui->WorkerButton->setStyleSheet("background-color: white");
    m_ui->MinerButton->setStyleSheet("background-color: white");
    m_ui->LumberjackButton->setStyleSheet("background-color: white");
    m_ui->WorkerButton->setEnabled(true);
    m_ui->LumberjackButton->setEnabled(true);
    m_ui->MinerButton->setEnabled(true);
    m_ui->AssignCitizenButton->setEnabled(false);
    m_ui->CancelCitizenAssigningButton->setEnabled(false);
    m_ui->gameInfo->clear();
}

void MapWindow::assingCitizenButtonClicked()
{
    //Checks which Citizen button is pressed
    if (m_ui->WorkerButton->isEnabled())
    {
        clearWorkerManagement();

        //Creates BasicWorker
        std::shared_ptr<Course::WorkerBase> worker= gameengine_->addBasicWorker();

        //If there is enough space for citizen the worker is added
        if (worker != nullptr)
        {
            std::shared_ptr<Course::PlayerBase> current_player = handler_
                    ->getPlayer(gameengine_->getPlayerNumber());
            handler_->checkIfEnoughResources(current_player,
                                             Course::ConstResourceMaps
                                             ::BW_RECRUITMENT_COST);
            handler_->reduceResources(current_player,
                                      Course::ConstResourceMaps
                                      ::BW_RECRUITMENT_COST);
            updateResources(handler_->getResourceVector(current_player));
            mapDrawer();
            turn_end_ = true;
        }
        else
        {
            QString text = "There is no space for citizen";
            m_ui->gameInfo->setText(text);
        }
    }
    else if (m_ui->MinerButton->isEnabled())
    {
        clearWorkerManagement();

        //Creates Miner
        std::shared_ptr<Course::WorkerBase> worker= gameengine_->addMiner();

        //If there is enough space for citizen the miner is added
        if (worker != nullptr)
        {
            std::shared_ptr<Course::PlayerBase> current_player = handler_
                    ->getPlayer(gameengine_->getPlayerNumber());
            handler_->checkIfEnoughResources(current_player,MINER_RECRUITMENT_COST);
            handler_->reduceResources(current_player,MINER_RECRUITMENT_COST);
            updateResources(handler_->getResourceVector(current_player));
            mapDrawer();
            turn_end_ = true;
        }
        else
        {
            QString text = "There is no space for citizen";
            m_ui->gameInfo->setText(text);
        }
    }

    else if (m_ui->LumberjackButton->isEnabled())
    {
        clearWorkerManagement();

        //Creates Lumberjack
        std::shared_ptr<Course::WorkerBase> worker= gameengine_->addLumberjack();

        //If there is enough space for citizen the Lumberjack is added
        if (worker != nullptr)
        {
            std::shared_ptr<Course::PlayerBase> current_player = handler_
                    ->getPlayer(gameengine_->getPlayerNumber());
            handler_->checkIfEnoughResources(current_player,LUMBERJACK_RECRUITMENT_COST);
            handler_->reduceResources(current_player,LUMBERJACK_RECRUITMENT_COST);
            updateResources(handler_->getResourceVector(current_player));
            mapDrawer();
            turn_end_ = true;
        }
        else
        {
            QString text = "There is no space for citizen";
            m_ui->gameInfo->setText(text);
        }
    }
}

void MapWindow::cancelCitizenAssigningButtonClicked()
{
    clearWorkerManagement();
}


void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_customscene->drawItem(obj);
}

void MapWindow::updateResources(std::vector<int> resource_vector)
{
    m_ui->MoneyLabel->setText(QString::number(resource_vector.at(0)));
    m_ui->FoodLabel->setText(QString::number(resource_vector.at(1)));
    m_ui->WoodLabel->setText(QString::number(resource_vector.at(2)));
    m_ui->StoneLabel->setText(QString::number(resource_vector.at(3)));
    m_ui->OreLabel->setText(QString::number(resource_vector.at(4)));
}

void MapWindow::mapDrawer()
{
    //Goes through tiles and draws them
    for (auto tile: manager_->getTilesForMap())
    {
        MapWindow::drawItem(tile);
        if (tile->getBuildingCount() > 0)
        {
            //Goes through tiles buildings and draws them
            for (auto building : tile->getBuildings())
            {
                building->onBuildAction();
                MapWindow::drawItem(building);
            }
        }
        if (tile->getWorkerCount() > 0)
        {
            //Goes through tiles citizens and draws them
            for (auto citizen : tile->getWorkers())
            {
                MapWindow::drawItem(citizen);
            }
        }
    }
}

bool MapWindow::checkWin()
{
    std::shared_ptr<Course::PlayerBase> current_player = handler_->getPlayer(
                gameengine_->getPlayerNumber());
    std::vector<int> resource_vector = handler_->getResourceVector(current_player);
    Course::ResourceMap WINNER_RESOURCES = WINNING_RESOURCES;
    int counter = 0;

    //Goes through current player resources returning false if amount of resource
    //is less than winner_resources
    for (auto i : WINNER_RESOURCES)
    {
        if((resource_vector.at(counter) < i.second))
        {
            return false;
        }
        counter +=1;
    }
    return true;
}

void MapWindow::dialogStory()
{
    m_ui->gameInfo->clear();
    Dialogstory* dialogstory = new Dialogstory(this);
    dialogstory->setModal(true);
    dialogstory->exec();
}

void MapWindow::transferDialogInformation(string object, string action,
                                          string direction)
{
    if (object == "Outpost")
    {

        std::shared_ptr<Course::BuildingBase> outpost = gameengine_
                ->modifyOutpost(action);
        //If outpost was created in game_engine
        if (outpost != nullptr)
        {
            if (action == "build")
            {
                //Reduces and updates player resources
                std::shared_ptr<Course::PlayerBase> current_player = handler_
                        ->getPlayer(gameengine_->getPlayerNumber());
                handler_->reduceResources(current_player,
                                          Course::ConstResourceMaps
                                          ::OUTPOST_BUILD_COST);
                updateResources(handler_->getResourceVector(current_player));
                mapDrawer();
                turn_end_ = true;
            }
            else if (action == "remove")
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
        else
        {
            m_ui->gameInfo->setText("You need to remove all citizens and buildings"
                                    " from outpost tile and neighbour tiles!");
        }
    }
    if (object == "Farm")
    {
        std::shared_ptr<Course::BuildingBase> farm = gameengine_->modifyFarm(action);
        //If Farm was created in game_engine
        if (farm != nullptr)
        {
            if (action == "build")
            {
                //Reduces and updates player resources
                std::shared_ptr<Course::PlayerBase> current_player = handler_
                        ->getPlayer(gameengine_->getPlayerNumber());
                handler_->reduceResources(current_player,
                                          Course::ConstResourceMaps
                                          ::FARM_BUILD_COST);
                updateResources(handler_->getResourceVector(current_player));
                mapDrawer();
                turn_end_ = true;
            }
            else if (action == "remove")
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
    }
    if (object == "Oremine")
    {
        std::shared_ptr<Course::BuildingBase> oremine = gameengine_
                ->modifyOremine(action);
        //If Oremine was created in game_engine
        if (oremine != nullptr)
        {
            if (action == "build")
            {
                //Reduces and updates player resources
                std::shared_ptr<Course::PlayerBase> current_player = handler_
                        ->getPlayer(gameengine_->getPlayerNumber());
                handler_->reduceResources(current_player,OREMINE_BUILD_COST);
                updateResources(handler_->getResourceVector(current_player));
                mapDrawer();
                turn_end_ = true;
            }
            else if (action == "remove")
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
    }
    if (object == "Bank")
    {
        std::shared_ptr<Course::BuildingBase> bank = gameengine_
                ->modifyBank(action);
        //If Bank was created in game_engine
        if (bank != nullptr)
        {
            if (action == "build")
            {
                //Reduces and updates player resources
                std::shared_ptr<Course::PlayerBase> current_player = handler_
                        ->getPlayer(gameengine_->getPlayerNumber());
                handler_->reduceResources(current_player,BANK_BUILD_COST);
                updateResources(handler_->getResourceVector(current_player));
                mapDrawer();
                turn_end_ = true;
            }
            else if (action == "remove")
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
    }
    if (object == "Sawmill")
    {
        std::shared_ptr<Course::BuildingBase> sawmill = gameengine_
                ->modifySawmill(action);
        //If Sawmill was created in game_engine
        if (sawmill != nullptr)
        {
            if (action == "build")
            {
                //Reduces and updates player resources
                std::shared_ptr<Course::PlayerBase> current_player = handler_
                        ->getPlayer(gameengine_->getPlayerNumber());
                handler_->reduceResources(current_player,SAWMILL_BUILD_COST);
                updateResources(handler_->getResourceVector(current_player));
                mapDrawer();
                turn_end_ = true;
            }
            else if (action == "remove")
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
    }
    if (object == "BasicWorker")
    {
        std::shared_ptr<Course::WorkerBase> worker = gameengine_
                ->modifyWorker(action,direction,object);
        if (action == "move")
        {
            //If worker wasn't created in game engine
            if (worker == nullptr)
            {
                QString text =
                        "You can't move citizen out of map or out of your "
                        "territory or tile that is full of citizens!";
                m_ui->gameInfo->setText(text);
            }
            else
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
        else
        {
            mapDrawer();
            turn_end_ = true;
        }
    }
    if (object == "Lumberjack")
    {
        std::shared_ptr<Course::WorkerBase> worker = gameengine_
                ->modifyWorker(action,direction,object);
        if (action == "move")
        {
            //If worker wasn't created in game engine
            if (worker == nullptr)
            {
                QString text =
                        "You can't move citizen out of map or out of your "
                        "territory or tile that is full of citizens!";
                m_ui->gameInfo->setText(text);
            }
            else
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
        else
        {
            mapDrawer();
            turn_end_ = true;
        }
    }
    if (object == "Miner")
    {
        std::shared_ptr<Course::WorkerBase> worker = gameengine_
                ->modifyWorker(action,direction,object);
        if (action == "move")
        {
            //If worker wasn't created in game engine
            if (worker == nullptr)
            {
                QString text =
                        "You can't move citizen out of map or out of your "
                        "territory or tile that is full of citizens!";
                m_ui->gameInfo->setText(text);
            }
            else
            {
                mapDrawer();
                turn_end_ = true;
            }
        }
        else
        {
            mapDrawer();
            turn_end_ = true;
        }
    }
}

void MapWindow::possibleBuildingVectorUpdater()

{
    possible_buildings_vector_ = {};
    std::shared_ptr<Course::PlayerBase> current_player = handler_
            ->getPlayer(gameengine_->getPlayerNumber());

    //Creates a vector that contains all prices for buildings
    std::vector<std::pair<Course::ResourceMap, std::string>> building_cost_vector
    {{Course::ConstResourceMaps::FARM_BUILD_COST,"Farm"},
        {Course::ConstResourceMaps::OUTPOST_BUILD_COST,"Outpost"},
        {OREMINE_BUILD_COST,"Oremine"},{BANK_BUILD_COST,"Bank"},{SAWMILL_BUILD_COST,"Sawmill"}};

    //Goes through buildings in building_cost_vector
    for (auto item :building_cost_vector)
    {
        //if player has enough resources the building is addded to
        //possible_buildings_vector
        if(handler_->checkIfEnoughResources(current_player,item.first))
        {
            possible_buildings_vector_.push_back(item.second);
        }
    }
}


void MapWindow::GetHighScore(std::shared_ptr<Course::PlayerBase> player)
{
       map<int, std::string> highscore_map;
       std::vector<pair<std::string, int>> resource_pair_vector;
       std::vector<std::shared_ptr<Course::PlayerBase>> players = handler_->getPlayers();
       std::string player_name = player->getName();

       //Calculates current player's final score and updates player's score to UI
       std::vector<int> resource_vector = handler_->getResourceVector(player);
       int sum = accumulate(resource_vector.begin(),resource_vector.end(),0);
       int round_number = (gameengine_->getRound()).toInt();
       int final_score = sum*(target_rounds/round_number);
       m_ui->WinningLabelYourScoreNumber->setText(QString::number(final_score));

       //Reads txt-file containing highscores storing them into map
       string line;
       ifstream myfile ("HighScore.txt");
       vector<string> result;

       if (myfile.is_open())
       {
           while (getline(myfile,line))
           {
               if (line != "")
               {
                   string input(line);
                   boost::split(result, input, boost::is_any_of(","));
                   highscore_map.insert({std::stoi(result[1]),result[0]});
               }
           }
           myfile.close();
       }

       //If there are over 5 elements in the map the player's score is added
       //as it is
       if(highscore_map.size()< 5)
       {
           highscore_map.insert({final_score,player_name});
       }


       //If map's lowest score is lower than player's score the it is erased and
       //players score is added to map
       else if((highscore_map.begin())->first < final_score)
       {
           highscore_map.erase(highscore_map.begin()->first);
           highscore_map.insert({final_score,player_name});
       }

       //New highscores are writen into txt-file.
       ofstream newFile ("HighScore.txt");
       if (newFile.is_open())
       {
           for (auto highscore: highscore_map)
           {
               newFile << highscore.second+","+
               std::to_string(highscore.first)+"\n"<<endl;
           }
           newFile.close();
       }


       //If there is only one value in map the UI is updated
       if(highscore_map.size() == 1)
       {
           QString txt = QString::fromStdString("1. "+highscore_map.rbegin()
           ->second)+" "+QString::number(highscore_map.rbegin()->first);
           m_ui->HighScoreLabel1->setText(txt);
       }

       else
       {
           int counter = 0;

           //Goes through every element in map in reverse order printing
           //map's key and value and updating correct label
           for (auto it1 = highscore_map.rbegin();  it1!=highscore_map.rend(); ++it1)
           {
               if(counter ==0)
               {
                   m_ui->HighScoreLabel1->setText(QString::fromStdString
                   ("1. "+it1->second)+" "+QString::number(it1->first));
                   counter +=1;
               }
                else if(counter ==1)
               {
                   m_ui->HighScoreLabel2->setText(QString::fromStdString
                  ("2. "+it1->second)+" "+QString::number(it1->first));
                   counter +=1;
               }
               else if(counter ==2)
               {
                   m_ui->HighScoreLabel3->setText(QString::fromStdString
                   ("3. "+it1->second)+" "+QString::number(it1->first));
                   counter +=1;
               }

               else if(counter ==3)
               {
                   m_ui->HighScoreLabel4->setText(QString::fromStdString
                   ("4. "+it1->second)+" "+QString::number(it1->first));
                   counter +=1;
               }
               else if(counter == 4)
               {
                   m_ui->HighScoreLabel5->setText(QString::fromStdString
                   ("5. "+it1->second)+" "+QString::number(it1->first));
                   counter +=1;
               }
           }
       }
}


