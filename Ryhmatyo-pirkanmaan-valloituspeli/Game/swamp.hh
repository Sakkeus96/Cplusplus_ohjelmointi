#ifndef SWAMP_HH
#define SWAMP_HH
#include "tiles/tilebase.h"
#include "customresourcemap.hh"
/**
 * @brief The Swamp class represents Forest in the gameworld.
 *
 * Forest has BasicProduction: \n
 * * Money = 3
 * * Food = 1
 * * Wood = 1
 * * Stone = 1
 * * Ore = 1
 *
 * Building in the swamp takes time. So buildings get extra hold-marker.
 *
 * Tile supports 1 building and 3 workers.
 */

class Swamp : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Swamp() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Swamp(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = SWAMP_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Swamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Swamp


#endif // SWAMP_HH
