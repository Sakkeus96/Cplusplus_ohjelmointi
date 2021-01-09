#ifndef CUSTOMRESOURCEMAP_HH
#define CUSTOMRESOURCEMAP_HH

#include "core/resourcemaps.h"
#include "core/basicresources.h"
#include <QObject>
#include <map>





// Gamesetup
const std::map<Course::BasicResource, int> STARTING_RESOURCES = {
    {Course::BasicResource::MONEY, 25},
    {Course::BasicResource::FOOD, 25},
    {Course::BasicResource::WOOD, 25},
    {Course::BasicResource::STONE, 25},
    {Course::BasicResource::ORE, 25}
};

const Course::ResourceMap WINNING_RESOURCES = {
    {Course::MONEY, 1000},
    {Course::FOOD, 1000},
    {Course::WOOD, 1000},
    {Course::STONE, 1000},
    {Course::ORE, 1000},
};

// Buildings
const Course::ResourceMap OREMINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 75},
    {Course::BasicResource::WOOD, 25},
    {Course::BasicResource::ORE, 25}
};
const Course::ResourceMap OREMINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::STONE, 5},
    {Course::BasicResource::ORE, 5}
};

const Course::ResourceMap BANK_BUILD_COST = {
    {Course::BasicResource::MONEY, 200},
    {Course::BasicResource::FOOD, 200},
    {Course::BasicResource::WOOD, 200},
    {Course::BasicResource::STONE, 200},
    {Course::BasicResource::ORE, 200}

};
const Course::ResourceMap BANK_PRODUCTION = {
    {Course::BasicResource::MONEY, 50}
};

const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::MONEY, 75},
    {Course::BasicResource::FOOD, 50},
    {Course::BasicResource::WOOD, 30}
};
const Course::ResourceMap SAWMILL_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::WOOD, 5}
};

// Tiles
const Course::ResourceMap MOUNTAIN_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 4},
    {Course::ORE, 4},
};

const Course::ResourceMap DESERT_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 1},
    {Course::WOOD, 1},
    {Course::STONE, 2},
    {Course::ORE, 1},
};

const Course::ResourceMap SWAMP_BP = {
    {Course::MONEY, 3},
    {Course::FOOD, 1},
    {Course::WOOD, 1},
    {Course::STONE, 1},
    {Course::ORE, 1},
};

const Course::ResourceMap ICEFIELD_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 1},
    {Course::WOOD, 1},
    {Course::STONE, 1},
    {Course::ORE, 1},
};

// Citizens
const Course::ResourceMapDouble MINER_WORKER_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.95},
    {Course::BasicResource::FOOD, 0.95},
    {Course::BasicResource::WOOD, 1.00},
    {Course::BasicResource::STONE, 1.15},
    {Course::BasicResource::ORE, 1.15}
};

const Course::ResourceMap MINER_RECRUITMENT_COST = {
    {Course::BasicResource::MONEY, 10},
    {Course::BasicResource::FOOD, 25},
    {Course::BasicResource::ORE, 5}
};
const Course::ResourceMapDouble LUMBERJACK_WORKER_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.95},
    {Course::BasicResource::FOOD, 0.95},
    {Course::BasicResource::WOOD, 1.30},
    {Course::BasicResource::STONE, 1.00},
    {Course::BasicResource::ORE, 1.00}
};

const Course::ResourceMap LUMBERJACK_RECRUITMENT_COST = {
    {Course::BasicResource::MONEY, 10},
    {Course::BasicResource::FOOD, 25},
    {Course::BasicResource::WOOD, 5}
};

const Course::ResourceMapDouble CUSTOM_BW_WORKER_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.95},
    {Course::BasicResource::FOOD, 1.15},
    {Course::BasicResource::WOOD, 1.00},
    {Course::BasicResource::STONE, 1.00},
    {Course::BasicResource::ORE, 1.00}
};



#endif // CUSTOMRESOURCEMAP_HH
