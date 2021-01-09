#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH
#include <iostream>
#include <map>

#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/coordinate.h"

#include "buildings/headquarters.h"
#include "buildings/outpost.h"
#include "buildings/farm.h"
#include "oremine.hh"
#include "bank.hh"
#include "sawmill.hh"

#include "workers/basicworker.h"
#include "workers/workerbase.h"
#include "miner.hh"
#include "lumberjack.hh"

#include "tiles/tilebase.h"

#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "customresourcemap.hh"


/**
 * @brief Gameengine take care of round system and keep a record of current
 * player. Gameengine also adds, move and free citizens and build or remove
 * buildings.
 */
class Gameengine
{
public:
    Gameengine();
    virtual ~Gameengine() = default;

    /**
     * @brief Take care of rounds and keep a record of current player
     * @post Exception guarantee: No-throw
     */
    void roundHandler();

    /**
     * @brief Gives players and playercount to gameeventhandler and saves
     * players and playercount
     * @param Names of the players
     * @param Number of players
     * @post Exception guarantee: Basic
     */
    void setPlayers(std::vector<std::string> players, int playercount);

    /**
     * @brief Changes playername std::string -> QString and returns it.
     * @return Qstring playername
     * @post Exception guarantee: No-throw
     */
    QString getPlayerName();

    /**
     * @brief Changes playernumber int -> QString and returns it.
     * @return Qstring playernumber
     * @post Exception guarantee: No-throw
     */
    QString getRound();

    /**
     * @brief Saves gameeventhandler and objectmanager
     * @param Gameeventhandler
     * @param Objectmanager
     * @post Exception guarantee: No-throw
     */
    void setHandlerAndManager(std::shared_ptr<GameEventHandler> handler,
                              std::shared_ptr<ObjectManager> manager);

    /**
     * @brief returns currentplayernumber
     * @return Currentplayernumber
     * @post Exception guarantee: No-throw
     */
    int getPlayerNumber();

    /**
     * @brief Create headquarters for players and set tiles owners
     * @return All headquarters that were created
     * @post Exception guarantee: None
     */
    std::vector<std::shared_ptr<Course::HeadQuarters>> startSetup();

    /**
     * @brief Saves map's heigth and width
     * @param Pair which have heigth and width
     * @post Exception guarantee: No-throw
     */
    void setHeightAndWidth(std::pair<int, int> size);

    /**
     * @brief Saves coordinates from mouse click event and check who own
     * tile in that coordinates
     * @return Pair which have number that tells who own the tile and the tile
     * @post Exception guarantee: Basic
     */
    std::pair<int, std::shared_ptr<Course::TileBase>> mouseEvent(QPointF point);

    /**
     * @brief Build or remove outpost. If removed tile's and neighbour tile's
     * ownership disappears. if build tile's and neighbout tile's owner is player
     * @param Action which is build or remove
     * @return Outpost that build, removed or nullptr pointer
     * @post Exception guarantee: None
     */
    std::shared_ptr<Course::BuildingBase> modifyOutpost(std::string action);

    /**
     * @brief Remove building from tile
     * @param Building type that will be removed
     * @param Tile where building is
     * @return Building that removed
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::BuildingBase> buildingRemover(
            std::string building, std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Build or remove farm
     * @param Action which is build or remove
     * @return Farm that build or removed
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::BuildingBase> modifyFarm(std::string action);

    /**
     * @brief Build or remove oremine
     * @param Action which is build or remove
     * @return Oremine that build or removed
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::BuildingBase> modifyOremine(std::string action);

    /**
     * @brief Move or free citizen. Nullptr tells that move failed
     * @param Action that tells what to do
     * @param Direction that tells where to move
     * @param Object that tells who is doing action
     * @return Citizen who moved, free'd or nullptr
     * @post Exception guarantee: None
     */
    std::shared_ptr<Course::WorkerBase> modifyWorker(
            std::string action, std::string direction, std::string object);

    /**
     * @brief Add basicworker at HQ tile. Nullptr tells that assign failed
     * @return Basicworker who is added or nullptr
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::WorkerBase> addBasicWorker();

    /**
     * @brief Build or remove sawmill
     * @param Action which is build or remove
     * @return Sawmill that build or removed
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::BuildingBase> modifySawmill(std::string action);

    /**
     * @brief Build or remove bank
     * @param Action which is build or remove
     * @return Bank that build or removed
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::BuildingBase> modifyBank(std::string action);

    /**
     * @brief Add miner at HQ tile. Nullptr tells that assign failed
     * @return Miner who is added or nullptr
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::WorkerBase> addMiner();

    /**
     * @brief Add lumberjack at HQ tile. Nullptr tells that assign failed
     * @return Lumberjack who is added or nullptr
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::WorkerBase> addLumberjack();
private:

    std::vector<std::shared_ptr<std::map<Course::BasicResource, int>>> resource_vector_;
    int roundcounter_ = 1;
    int currentplayernumber_ = 1;
    int playercount_;
    int height_;
    int width_;
    QPointF point_;
    std::vector<std::pair<int, int>> hq_coordinates_;
    std::vector<std::string> players_;
    std::shared_ptr<GameEventHandler> handler_ = nullptr;
    std::shared_ptr<ObjectManager> manager_ = nullptr;
};

#endif // GAMEENGINE_HH
