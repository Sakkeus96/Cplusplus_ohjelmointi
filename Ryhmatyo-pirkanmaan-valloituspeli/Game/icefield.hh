#ifndef ICEFIELD_HH
#define ICEFIELD_HH
#include "tiles/tilebase.h"
#include "customresourcemap.hh"
/**
 * @brief The Icefield class represents Forest in the gameworld.
 *
 * Icefield has BasicProduction: \n
 * * Money = 2
 * * Food = 1
 * * Wood = 1
 * * Stone = 1
 * * Ore = 1
 *
 *
 * Tile supports 1 building and 1 worker.
 */

class Icefield : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Icefield() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Icefield(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production = ICEFIELD_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Icefield() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Icefield


#endif // ICEFIELD_HH
