#include "gameengine.hh"
#include "string"
#include <QDebug>



Gameengine::Gameengine()
{

}

void Gameengine::roundHandler()
{
    if (currentplayernumber_ < playercount_)
    {
        ++currentplayernumber_;
    }
    else
    {
        currentplayernumber_ = 1;
        ++roundcounter_;
    }
}

void Gameengine::setPlayers(std::vector<std::string> players, int playercount)
{
    handler_->addPlayers(playercount, players);
    players_ = players;
    playercount_ = playercount;
}

QString Gameengine::getPlayerName()
{
    QString player = QString::fromStdString(players_.at(currentplayernumber_-1));
    return player;
}

QString Gameengine::getRound()
{
    QString round = QString::number(roundcounter_);
    return round;
}

void Gameengine::setHandlerAndManager(std::shared_ptr<GameEventHandler> handler,
                                      std::shared_ptr<ObjectManager> manager)
{
    handler_ = handler;
    manager_ = manager;
}

std::vector<std::shared_ptr<Course::HeadQuarters>> Gameengine::startSetup()
{
    std::vector<std::shared_ptr<Course::PlayerBase>> players = handler_->
            getPlayers();
    hq_coordinates_ = {{0,0},{0,height_-1},{width_-1,0},{width_-1,height_-1}};
    std::vector<std::shared_ptr<Course::HeadQuarters>> hqs;
    for (auto i = 0; i < playercount_; ++i)
    {
        std::shared_ptr<Course::HeadQuarters> hq (new Course::HeadQuarters
                                                  (handler_,manager_,
                                                   players.at(i)));
        Course::Coordinate coordinate = Course::Coordinate
                (hq_coordinates_.at(i).first,hq_coordinates_.at(i).second);
        std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
        tile->setOwner(players.at(i));
        tile->addBuilding(hq);
        hq->onBuildAction();
        hqs.push_back(hq);
    }
    return hqs;
}

void Gameengine::setHeightAndWidth(std::pair<int, int> size)
{
    height_ = size.first;
    width_ = size.second;
}

std::pair<int, std::shared_ptr<Course::TileBase>> Gameengine::mouseEvent(
        QPointF point)
{
    point_ = point;
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    if (tile->getOwner() != nullptr)
    {
        if (tile->getOwner()->getName() == players_.at(currentplayernumber_-1))
        {
           std::pair<int, std::shared_ptr<Course::TileBase>> own_tile =
           {1,tile};
           return own_tile;
        }
        else
        {
            std::pair<int, std::shared_ptr<Course::TileBase>> enemy_tile =
            {2,tile};
            return enemy_tile;
        }
    }
    else
    {
        std::pair<int, std::shared_ptr<Course::TileBase>> empty_tile = {0,tile};
        return empty_tile;
    }
}

std::shared_ptr<Course::BuildingBase> Gameengine::modifyOutpost(
        std::string action)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                currentplayernumber_);
    if (action == "build")
    {
        std::shared_ptr<Course::BuildingBase> outpost(new Course::Outpost(
                                                          handler_, manager_,
                                                          player));
        tile->setOwner(player);
        tile->addBuilding(outpost);
        outpost->onBuildAction();
        return outpost;
    }
    else
    {
        std::vector<Course::Coordinate> neighbourcoordinates = coordinate.neighbours();
        for (auto neighbour : neighbourcoordinates)
        {
            if (neighbour.x() >= 0 && neighbour.y() >= 0 && neighbour.x() < width_ && neighbour.y() < height_)
            {
                if (manager_->getTile(neighbour)->getOwner() == player)
                {
                    if (manager_->getTile(neighbour)->getBuildingCount() > 0 ||
                            manager_->getTile(neighbour)->getWorkerCount() > 0)
                    {
                        std::shared_ptr<Course::BuildingBase> outpost = nullptr;
                        return outpost;
                    }
                }
            }
        }
        if (tile->getBuildingCount() > 1 || tile->getWorkerCount() > 0)
        {
            std::shared_ptr<Course::BuildingBase> outpost = nullptr;
            return outpost;
        }
        else
        {
            std::shared_ptr<Course::BuildingBase> outpost = buildingRemover(
                        "Outpost", tile);
            for (auto neighbour : neighbourcoordinates)
            {
                if (neighbour.x() >= 0 && neighbour.y() >= 0 && neighbour.x() < width_ && neighbour.y() < height_)
                {
                    manager_->getTile(neighbour)->setOwner(nullptr);
                }
            }
            tile->setOwner(nullptr);
            return outpost;
        }
    }
}

std::shared_ptr<Course::BuildingBase> Gameengine::buildingRemover(
        std::string building, std::shared_ptr<Course::TileBase> tile)
{
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings = tile->
            getBuildings();
    std::shared_ptr<Course::BuildingBase> returnbuilding;
    for (auto buildingfromvector : buildings)
    {
        if (buildingfromvector->getType() == building)
        {
            tile->removeBuilding(buildingfromvector);
            returnbuilding = buildingfromvector;
            break;
        }
    }
    return returnbuilding;
}

std::shared_ptr<Course::BuildingBase> Gameengine::modifyFarm(std::string action)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                currentplayernumber_);
    if (action == "build")
    {
        std::shared_ptr<Course::BuildingBase> farm(new Course::Farm(
                                                       handler_, manager_,
                                                       player));
        tile->addBuilding(farm);
        return farm;
    }
    else
    {
        std::shared_ptr<Course::BuildingBase> farm = buildingRemover("Farm",
                                                                     tile);
        return farm;
    }
}

std::shared_ptr<Course::BuildingBase> Gameengine::modifyOremine(std::string
                                                                action)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                currentplayernumber_);
    if (action == "build")
    {
        std::shared_ptr<Course::BuildingBase> oremine(new Oremine(
                                                          handler_,
                                                          manager_, player));
        tile->addBuilding(oremine);
        return oremine;
    }
    else
    {
        std::shared_ptr<Course::BuildingBase> oremine = buildingRemover(
                    "Oremine", tile);
        return oremine;
    }
}

std::shared_ptr<Course::BuildingBase> Gameengine::modifyBank(std::string
                                                                action)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                currentplayernumber_);
    if (action == "build")
    {
        std::shared_ptr<Course::BuildingBase> bank(new Bank(
                                                          handler_,
                                                          manager_, player));
        tile->addBuilding(bank);
        return bank;
    }
    else
    {
        std::shared_ptr<Course::BuildingBase> bank = buildingRemover(
                    "Bank", tile);
        return bank;
    }
}

std::shared_ptr<Course::BuildingBase> Gameengine::modifySawmill(std::string
                                                                action)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::shared_ptr<Course::PlayerBase> player = handler_->getPlayer(
                currentplayernumber_);
    if (action == "build")
    {
        std::shared_ptr<Course::BuildingBase> sawmill(new Sawmill(
                                                          handler_,
                                                          manager_, player));
        tile->addBuilding(sawmill);
        return sawmill;
    }
    else
    {
        std::shared_ptr<Course::BuildingBase> sawmill = buildingRemover(
                    "Sawmill", tile);
        return sawmill;
    }
}

std::shared_ptr<Course::WorkerBase> Gameengine::modifyWorker(
        std::string action, std::string direction, std::string object)
{
    Course::Coordinate coordinate = Course::Coordinate(point_.x(),point_.y());
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    std::vector<std::shared_ptr<Course::WorkerBase>> workers = tile->getWorkers();
    std::shared_ptr<Course::WorkerBase> returnworker;
    for (auto workerfromvector : workers)
    {
        if (workerfromvector->getType() == object)
        {
            if (action == "move")
            {
                Course::Direction modifieddirection;
                //N moves S because of course code
                if (direction == "N")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::S, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::S, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::S, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::S, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::S;
                    }
                }
                //NE moves SE because of course code
                else if (direction == "NE")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::SE, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::SE, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::SE, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::SE, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::SE;
                    }
                }
                else if (direction == "E")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::E, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::E, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::E, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::E, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::E;
                    }
                }
                //SE moves NE because of course code
                else if (direction == "SE")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::NE, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::NE, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::NE, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::NE, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::NE;
                    }
                }
                //S moves N because of course code
                else if (direction == "S")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::N, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::N, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::N, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::N, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::N;
                    }
                }
                //SW moves NW because of course code
                else if (direction == "SW")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::NW, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::NW, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::NW, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::NW, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::NW;
                    }
                }
                else if (direction == "W")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::W, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::W, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::W, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::W, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::W;
                    }
                }
                //NW moves SW because of course code
                else if (direction == "NW")
                {
                    //Check that citizen stays in the map area after move
                    if (coordinate.neighbour_at(Course::Direction::SW, 1).x() < 0
                            || coordinate.neighbour_at(Course::Direction::SW, 1)
                            .y() < 0 || coordinate.neighbour_at(Course::Direction::SW, 1).x() > width_ - 1
                            || coordinate.neighbour_at(Course::Direction::SW, 1)
                            .y() > height_ - 1)
                    {
                        modifieddirection = Course::Direction::END;
                    }
                    else
                    {
                        modifieddirection = Course::Direction::SW;
                    }
                }
                if (modifieddirection != Course::Direction::END)
                {
                    coordinate.travel(modifieddirection,1);
                    if (workerfromvector->canBePlacedOnTile(manager_->getTile(coordinate)))
                    {
                        tile->removeWorker(workerfromvector);
                        tile = manager_->getTile(coordinate);
                        tile->addWorker(workerfromvector);
                        returnworker = workerfromvector;
                        break;
                    }
                    else
                    {
                        returnworker = nullptr;
                        break;
                    }
                }
                else
                {
                    returnworker = nullptr;
                    break;
                }
            }
            else
            {
                tile->removeWorker(workerfromvector);
                returnworker = workerfromvector;
            }
        }
    }
    return returnworker;
}

  std::shared_ptr<Course::WorkerBase> Gameengine::addBasicWorker()
{
      std::vector<std::shared_ptr<Course::PlayerBase>> players = handler_
              ->getPlayers();
    std::shared_ptr<Course::WorkerBase> worker (new Course::BasicWorker
                                                (handler_,manager_, players.at
                                                 (currentplayernumber_-1),1, Course::ConstResourceMaps::BW_RECRUITMENT_COST,CUSTOM_BW_WORKER_EFFICIENCY));
    Course::Coordinate coordinate = Course::Coordinate(
                hq_coordinates_.at(currentplayernumber_-1).first,
                hq_coordinates_.at(currentplayernumber_-1).second);
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    if (tile->hasSpaceForWorkers(1))
    {
        tile->setOwner(players.at(currentplayernumber_-1));
        tile->addWorker(worker);
    }
    else
    {
        worker = nullptr;
    }
    return worker;

}

  std::shared_ptr<Course::WorkerBase> Gameengine::addLumberjack()
{
      std::vector<std::shared_ptr<Course::PlayerBase>> players = handler_
              ->getPlayers();
      std::shared_ptr<Course::WorkerBase> worker (new Lumberjack(handler_,manager_, players.at(currentplayernumber_-1)));


    Course::Coordinate coordinate = Course::Coordinate(
                hq_coordinates_.at(currentplayernumber_-1).first,
                hq_coordinates_.at(currentplayernumber_-1).second);
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    if (tile->hasSpaceForWorkers(1))
    {
        tile->setOwner(players.at(currentplayernumber_-1));
        tile->addWorker(worker);
    }
    else
    {
        worker = nullptr;
    }
    return worker;

}

  std::shared_ptr<Course::WorkerBase> Gameengine::addMiner()
{
      std::vector<std::shared_ptr<Course::PlayerBase>> players = handler_
              ->getPlayers();
    std::shared_ptr<Course::WorkerBase> worker (new Miner
                                                (handler_,manager_, players.at
                                                 (currentplayernumber_-1),1));
    Course::Coordinate coordinate = Course::Coordinate(
                hq_coordinates_.at(currentplayernumber_-1).first,
                hq_coordinates_.at(currentplayernumber_-1).second);
    std::shared_ptr<Course::TileBase> tile = manager_->getTile(coordinate);
    if (tile->hasSpaceForWorkers(1))
    {
        tile->setOwner(players.at(currentplayernumber_-1));
        tile->addWorker(worker);
    }
    else
    {
        worker = nullptr;
    }
    return worker;

}

int Gameengine::getPlayerNumber()
{
    return currentplayernumber_;
}

