#ifndef BANK_HH
#define BANK_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include "objectmanager.hh"
#include "gameeventhandler.hh"
#include "core/playerbase.h"


static const Course::ResourceMap BANK_PRODUCTIONMAP = {

};

/**
 * @brief The Bank class represents a player's Bank-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Radius: 1 tiles\n
 *
 */
class Bank : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Bank() = delete;

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
    explicit Bank(
            const std::shared_ptr<GameEventHandler>& eventhandler,
            const std::shared_ptr<ObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = BANK_BUILD_COST,
            const Course::ResourceMap& production = BANK_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Bank() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Bank



#endif // BANK_HH
