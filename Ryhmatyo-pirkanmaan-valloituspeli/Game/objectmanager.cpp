#include "objectmanager.hh"
#include <iostream>
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "mountain.hh"
#include "desert.hh"
#include "icefield.hh"
#include "swamp.hh"
#include "tiles/tilebase.h"

ObjectManager::ObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>>
                             &tiles)
{
    all_titles_ = tiles;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate
                                                         &coordinate)
{
    std::shared_ptr<Course::TileBase> Tile_pointer = nullptr;
    for (std::shared_ptr<Course::TileBase> Tile : all_titles_)
    {
        if (Tile->getCoordinate() == coordinate)
        {
            std::shared_ptr<Course::TileBase> Tile_pointer = Tile;
            return Tile_pointer;
        }
    }
    return Tile_pointer;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    std::shared_ptr<Course::TileBase> Tile_pointer = nullptr;
    for (std::shared_ptr<Course::TileBase> Tile:  all_titles_)
    {
        if (Tile->ID == id)
        {
            std::shared_ptr<Course::TileBase> Tile_pointer = Tile;
            return Tile_pointer;
        }
    }
    return Tile_pointer;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(
        const std::vector<Course::Coordinate> &coordinates)
{
    std::shared_ptr<Course::TileBase> Tile_pointer = nullptr;
    std::vector<std::shared_ptr<Course::TileBase>> Tile_Vector {};

    //Goes throug given coordinates and then goes through tiles, when
    //right tile with same coordinate is found it is added to Tile Pointer vector
    for (auto coordinate: coordinates)
    {
       for (std::shared_ptr<Course::TileBase> Tile:  all_titles_)
       {
           if (Tile->getCoordinate() == coordinate)
           {
               std::shared_ptr<Course::TileBase> Tile_pointer = Tile;
               Tile_Vector.push_back(Tile_pointer);
           }
       }
    }
    return Tile_Vector;
}


std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTilesForMap()
{
    return all_titles_;
}

void ObjectManager::updateTileProduction(
        std::shared_ptr<Course::PlayerBase> player)
{
    for (auto tile : all_titles_)
    {
        if (tile->getOwner() != nullptr)
            {

            //Tiles resources are taking into account if tile is owned by player
            //and there if are player's building or worker on the tile
            if (tile->getOwner() == player && (tile->getBuildingCount() > 0
                                               || tile->getWorkerCount() > 0))
            {
                tile->generateResources();
            }
        }
    }
}

