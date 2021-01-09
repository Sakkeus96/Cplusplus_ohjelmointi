#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


#include <map>
#include <iostream>
#include <math.h>
#include <fstream>


#include "dialog.hh"
#include "dialogtile.hh"
#include "dialoginfo.hh"
#include "dialogstory.hh"

#include "core/resourcemaps.h"
#include "core/worldgenerator.h"

#include "custommapitem.hh"
#include "customgamescene.hh"
#include "customworldgenerator.hh"

#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/tilebase.h"
#include "mountain.hh"
#include "desert.hh"
#include "icefield.hh"
#include "swamp.hh"

#include "workers/basicworker.h"

#include "gameengine.hh"
#include "gameeventhandler.hh"
#include "objectmanager.hh"

/**
 * @brief The MapWindow object is the main window of the game. All the elements
 * of the game are attached to it. The ObjectManager, GameEventHandler and
 * GameEngine all works through it.
 */


namespace Ui {
class MapWindow;
}

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

    /**
     * @brief draw a new item to the map.
     * @param obj shared ptr to the object
     * @post Exception guarantee: None
     */
    void drawItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief creates a starting dialog and opens it
     */
    void dialog();

    /**
     * @brief updates MapWindows resource labels to equate with given vector's
     * values
     * @param Vector containing resource values
     * @post Exception guarantee: Basic
     */
    void updateResources(std::vector<int>);

    /**
     * @brief Goes through game's all tiles drawing them and also drawing
     * workers and buildings on them.
     * @post Exception guarantee: None
     */
    void mapDrawer();

    /**
     * @brief Checks current player resources comparing them to resources needed
     * to win the game
     * @return
     * True - If player has enough resources to win. \n
     * False - If player hasn't enough resources to win. \n
     * @post Exception guarantee: Basic
     */
    bool checkWin();

    /**
     * @brief Creates dialogstory-dialog
     * @post Exception guarantee: No-throw
     */
    void dialogStory();

public slots:

    /**
     * @brief Creates map, tiles, players and prepares Mainwindow for the firs
     * round of the game
     * @param playercount: int, that tells the amount of players
     * @param playeres: string vector that contains player names
     * @post Exception guarantee: None
     */
    void setPlayers(int playercount, std::vector<std::string> players);

    /**
     * @brief Calculates current players resources. Cleares and updates Mapwindow
     * for next player and checks if next player is winner.
     * @post Exception guarantee: None
     */
    void endTurn();

    /**
     * @brief Checks where player has clicked, if clicked on own or no-ones area
     * opens dialog or if clicked on enemys updates gameInfo text browser.
     * @param QPointF point that describes where player has clicked on the map
     * @post Exception guarantee: None
     */
    void transferPointer(QPointF point);

    /**
     * @brief Checks can player add a Worker and then opens assigning button
     * @post Exception guarantee: Basic
     */
    void workerButtonClicked();

    /**
     * @brief Sets Citizen Management section to its initial stage
     * @post Exception guarantee: No-throw
     */
    void clearWorkerManagement();

    /**
     * @brief Checks which citizen button is pressed and adds proper citizen if
     * there is enough space
     * @post Exception guarantee: None
     */
    void assingCitizenButtonClicked();

    /**
     * @brief Sets Citizen Management section to its initial stage by calling
     * clearWorkerManagement-function
     * @post Exception guarantee: No-throw
     */
    void cancelCitizenAssigningButtonClicked();

    /**
     * @brief Gets information from dialog. Based on that information: moves
     * citizens, builds and reduces player resources or removes buildings.
     * @param string object: object name
     * @param string action: action that player has made
     * @param string direction: direction that player has give to the citizen
     * @post Exception guarantee: No-throw
     */
    void transferDialogInformation(std::string object, std::string action,
                                   std::string direction);

    /**
     * @brief Checks what are the buildings to which player has enough resources,
     * and adds them to vector
     * @post Exception guarantee: Basic
     */
    void possibleBuildingVectorUpdater();

    /**
     * @brief Checks can player add a Miner and then opens assigning button
     * @post Exception guarantee: Basic
     */
    void minerButtonClicked();

    /**
     * @brief Checks can player add a Lumberjack and then opens assigning button
     * @post Exception guarantee: Basic
     */
    void lumberjackButtonClicked();

    /**
     * @brief Opens the ResourceInfo dialog
     * @post Exception guarantee: No-throw
     */
    void resourceInfoButtonClicked();

    /**
     * @brief Calculates player highscore and stores it to txt-file. Compares
     * highscores and then updates best 5 highscores into WinningWidget
     * @param player: shared pointer to winner player
     * @post Exception guarantee: None
     */
    void GetHighScore(std::shared_ptr<Course::PlayerBase> player);

signals:
    void dataGiver(std::pair<int, std::shared_ptr<Course::TileBase>> owner,
                   std::vector<std::string> possible_buildings_vector);

private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<CustomGameScene> m_customscene = nullptr;
    std::shared_ptr<GameEventHandler> handler_ = nullptr;
    std::shared_ptr<ObjectManager> manager_ = nullptr;
    std::shared_ptr<Gameengine> gameengine_ = nullptr;
    std::vector<std::string> possible_buildings_vector_ = {};
    bool turn_end_ = false;
    int target_rounds = 250;


};

#endif // MapWINDOW_HH

