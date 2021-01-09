#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH
#include "interfaces/iobjectmanager.h"
#include "core/playerbase.h"


/**
 * @brief The ObjectManager class keeps track on game map's tiles, adding and
 * returning pointers them when necessary. ObjectManager also can starts a
 * player's tile resource calculation with its updateTileproduction function.
 */

class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();
    virtual ~ObjectManager() = default;
    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles a vector that contains the Tiles to be added.
     * @post The tile-pointers in the vector are stored in the ObjectManager.
     * Exception Guarantee: Basic
     *
     */
    virtual void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /**
     * @brief Returns a shared pointer to a Tile that has specified coordinate.
     * @param coordinate Requested Tile's Coordinate
     * @return a pointer to a Tile that has the given coordinate.
     * If no for the coordinate exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    /**
     * @brief Returns a shared pointer to a Tile that has specified ID
     * @param id Tile's ObjectId.
     * @return a pointer to the Tile that has the given ID
     * If no for the id exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    /**
     * @brief Returns a vector of shared pointers to Tiles specified by
     * a vector of Coordinates.
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector of that contains pointers to Tile's that match
     * the coordinates. The vector is empty if no matches were made.
     * @post Exception Guarantee: Basic
     */
    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);
    
    /**
     * @brief Returns a vector of shared pointers to Tile-objects
     * @return Vector of that contains shared pointers to Tile-objects.
     * The vector is there are no added Tile-objects in ObjectManager class
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTilesForMap();


    /**
     * @brief Updates given players Tile-production, adding tile related
     * resources to players total resources. Tile-production is taken into
     * account if tiles are under player rule and if player has a worker or
     * on the tile building.
     * @param Shared pointer to player whose tiles production want to be
     * updated
     * @post Exception guarantee: Basic
     */
    void updateTileProduction(std::shared_ptr<Course::PlayerBase> player);
private:
     // For vector for map tiles
    std::vector<std::shared_ptr<Course::TileBase>> all_titles_ {};

};

#endif // OBJECTMANAGER_HH
