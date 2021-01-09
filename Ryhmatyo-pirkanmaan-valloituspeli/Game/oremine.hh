#ifndef OREMINE_HH
#define OREMINE_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "core/playerbase.h"


/**
 * @brief The Outpost class represents a player's Oremine-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Radius: 1 tiles\n
 *
 */
class Oremine : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Oremine() = delete;

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
    explicit Oremine(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<ObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = OREMINE_BUILD_COST,
            const Course::ResourceMap& production = OREMINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Oremine() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Oremine



#endif // OREMINE_HH
