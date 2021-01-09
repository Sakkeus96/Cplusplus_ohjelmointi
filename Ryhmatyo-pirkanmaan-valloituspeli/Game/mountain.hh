#ifndef MOUNTAIN_HH
#define MOUNTAIN_HH
#include "tiles/tilebase.h"
#include "customresourcemap.hh"
/**
 * @brief The Forest class represents Mountain in the gameworld.
 *
 * Forest has BasicProduction: \n
 * * Money = 2
 * * Food = 0
 * * Wood = 0
 * * Stone = 4
 * * Ore = 4
 *
 * Building in the mountain takes time. So buildings get extra hold-marker.
 *
 * Tile supports 3 buildings and 3 workers.
 */

class Mountain : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Mountain() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Mountain(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 3,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = MOUNTAIN_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Mountain() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Mountain


#endif // MOUNTAIN_HH
