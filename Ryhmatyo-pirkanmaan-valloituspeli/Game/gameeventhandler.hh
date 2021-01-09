#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH
#include "interfaces/igameeventhandler.h"
#include "core/basicresources.h"
#include "core/playerbase.h"
#include <map>
#include "customresourcemap.hh"
#include "core/resourcemaps.h"
#include "objectmanager.hh"


class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();

    virtual ~GameEventHandler() = default;

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     * @post Exception guarantee: Basic
     */
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     * @post Exception guarantee: Basic
     */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
    /**
     * @brief Takes number of players and their names and creates players,
     * saving created player pointers to vector
     * @param playerCount int, that represents amount of players
     * @param players vector, that contains players name
     * @post Exception guarantee: Basic
     */
    void addPlayers(int playerCount,std::vector<std::string> players);

    /**
     * @brief Returns a vector that contains pointers to player-objects
     * @return Returns a vector that contains pointers to player-objects
     * @post Exception guarantee: No-throw
     */
    std::vector<std::shared_ptr<Course::PlayerBase>> getPlayers();

    /**
     * @brief Returns a pointer to specific player when its playernumber is
     * given
     * @param a specific player's ordinal player number
     * @return pointer to specific player
     * @post Exception guarantee: Basic
     */
    std::shared_ptr<Course::PlayerBase> getPlayer(int playerNumber);

    /**
     * @brief Returns a map containing players' resources
     * @return A map, which key is player pointer and value a map which key is
     * basic resource and value amount of resource
     * @post Exception guarantee: No-throw
     */
    std::map<std::shared_ptr<Course::PlayerBase> ,std::map<Course::BasicResource,
    int>> getPlayerResources();

    /**
     * @brief Returns a vector containing player's resources that are in specific
     * order
     * @param a shared pointer to spesific player
     * @return A vector, that contains amounts of player's resources
     * @post Exception guarantee: Basic
     */
    std::vector<int> getResourceVector(std::shared_ptr<Course::PlayerBase>);

    /**
     * @brief Checks whether the player have enough resources
     * @param A shared pointer to specific player
     * @param A resourceMap that contains a resource that is going to be checked
     * @return
     * True - If player has enough resources. \n
     * False - If player hasn't enough resources. \n
     * @post Exception guarantee: Basic
    */
    bool checkIfEnoughResources(std::shared_ptr<Course::PlayerBase> player,
                                Course::ResourceMap resources);

    /**
     * @brief Reduces a right amount of the specific player's resources
     * @param A shared pointer to specific player
     * @param A resourceMap that contains a resource that is going to be reduced
     * @post Exception guarantee: Basic
     */

    void reduceResources(std::shared_ptr<Course::PlayerBase> player,
                         Course::ResourceMap resources);

private:
    int playercount_;
    std::vector<std::shared_ptr<Course::PlayerBase>> players_;
    std::map<std::shared_ptr<Course::PlayerBase> ,std::map<Course::BasicResource,
    int>> player_resources_;

};



#endif // GAMEEVENTHANDLER_HH

