#include "gameeventhandler.hh"
#include <iostream>


GameEventHandler::GameEventHandler()
{

}


bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase>
                                       player, Course::ResourceMap resources)
{

    std::map<Course::BasicResource, int> player_resources =
            player_resources_[player];

    //If there is enough resources the new resource map and player's current
    //map of resources are merged and true is returned
    if (checkIfEnoughResources(player, resources))
    {
        std::map<Course::BasicResource, int> new_resource_map =
                Course::mergeResourceMaps(player_resources,resources);
        player_resources_[player] = new_resource_map;
        return true;
    }
    //If there are not enough resources the new resource map and player's current
    //map of resources are merged and false is returned
    else
    {
        std::map<Course::BasicResource, int> new_resource_map =
                Course::mergeResourceMaps(player_resources,resources);
        player_resources_[player] = new_resource_map;
        return false;
    }


}

void GameEventHandler::addPlayers(int playerCount, std::vector<std::string>
                                  players)
{
    playercount_ = playerCount;
    //Goes through every playe name, then creates and saves new player object
    //pointer into vector, then giving starting resources to created player
    for (auto player: players)
    {
        std::shared_ptr<Course::PlayerBase> player_pointer(new Course::
                                                           PlayerBase(player));
        players_.push_back(player_pointer);
        player_resources_[player_pointer] = STARTING_RESOURCES;
    }
}

std::vector<std::shared_ptr<Course::PlayerBase> > GameEventHandler::getPlayers()
{
    return players_;
}

std::shared_ptr<Course::PlayerBase> GameEventHandler::getPlayer(int playerNumber)
{
    return players_.at(playerNumber - 1);
}

std::map<std::shared_ptr<Course::PlayerBase>, std::map<Course::BasicResource,
int>> GameEventHandler::getPlayerResources()
{
    return player_resources_;
}

std::vector<int> GameEventHandler::getResourceVector(std::shared_ptr<Course
                                                     ::PlayerBase> player)
{
    std::map<Course::BasicResource, int> resource_per_player = player_resources_
            [player];

    //Creates a vector from player's resources in specific order
    std::vector<int> player_resources_vector = {resource_per_player[Course::MONEY],
                                resource_per_player[Course::FOOD],
                                resource_per_player[Course::WOOD],
                                resource_per_player[Course::STONE],
                                resource_per_player[Course::ORE]};
    return player_resources_vector;
}

bool GameEventHandler::checkIfEnoughResources(std::shared_ptr<Course::PlayerBase>
                                              player, Course::ResourceMap
                                              resources)
{
    std::map<Course::BasicResource, int> player_resources =  player_resources_
            [player];

    //Goes through given resources and given players resources
    for (std::pair<Course::BasicResource, int>  value : resources)
    {
        for (std::pair<Course::BasicResource, int>  player_value:
             player_resources)
        {
            //If there is same resource in both, and their substraction is
            //negative the false is returned
                if(player_value.first == value.first)
                {
                    if (player_value.second -abs(value.second) < 0)
                    {
                        return false;
                    }
                }
        }
    }
   return true;
}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                      Course::BasicResource resource, int amount)
{
            std::map<Course::BasicResource, int> player_resources =
                    player_resources_[player];
            std::map<Course::BasicResource, int> new_resource = {{resource,
                                                                  amount}};

            //If there is enough resources the new resource map and player's current
            //map of resources are merged and true is returned
            if (checkIfEnoughResources(player, new_resource))
            {
                std::map<Course::BasicResource, int> new_resource_map =
                        Course::mergeResourceMaps(player_resources,new_resource);
                player_resources_[player] = new_resource_map;
                return true;
            }
            //If there are not enough resources the new resource map and player's
            //current map of resources are merged and false is returned
            else
            {
                std::map<Course::BasicResource, int> new_resource_map =
                        Course::mergeResourceMaps(player_resources,new_resource);
                player_resources_[player] = new_resource_map;
                return false;
            }


}

void GameEventHandler::reduceResources(std::shared_ptr<Course::PlayerBase> player,
                                       Course::ResourceMap resources)
{
    std::map<Course::BasicResource, int> player_resources =  player_resources_
            [player];
    Course::ResourceMap new_resources {};

    //Goes through given resources adding them into new resource map with nega-
    //tive sign
    for (std::pair<Course::BasicResource, int>  value: resources)
    {
               new_resources[value.first] = -value.second;
    }
    //Merges new resource map with players current resource map
    std::map<Course::BasicResource, int> new_resource_map =
            Course::mergeResourceMaps(player_resources,new_resources);
    player_resources_[player] = new_resource_map;

}



