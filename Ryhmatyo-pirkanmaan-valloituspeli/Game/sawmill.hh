#ifndef SAWMILL_HH
#define SAWMILL_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "core/playerbase.h"


/**
 * @brief The Sawmill class represents a player's Outpost-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Radius: 1 tiles\n
 *
 */
class Sawmill : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Sawmill() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit Sawmill(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<ObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = SAWMILL_BUILD_COST,
            const Course::ResourceMap& production = SAWMILL_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Sawmill() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Sawmill



#endif // SAWMILL_HH
