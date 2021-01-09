#ifndef DESERT_HH
#define DESERT_HH
#include "tiles/tilebase.h"
#include "customresourcemap.hh"


/**
 * @brief The Desert class represents Forest in the gameworld.
 *
 * Desert has BasicProduction: \n
 * * Money = 1
 * * Food = 1
 * * Wood = 1
 * * Stone = 2
 * * Ore = 1
 *
 *
 * Tile supports 2 buildings and 3 workers.
 */
class Desert : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Desert() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Desert(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 2,
              const unsigned int& max_work = 2,
              const Course::ResourceMap& production = DESERT_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Desert() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Desert


#endif // Desert_HH
