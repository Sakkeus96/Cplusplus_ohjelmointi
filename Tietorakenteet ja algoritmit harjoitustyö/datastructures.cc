// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::stop_count()
{
    return stops_.size();
}

void Datastructures::clear_all()
{
    stops_.clear();
    regions_.clear();
    stops_in_order_ = {NO_STOP};
    stops_changed_ = true;
    coordinates_changed_ = true;
    min_coord_changed_ = true;
    max_coord_changed_ = true;
    max_stop_ = NO_STOP;
    max_distance_ = -1;
    min_stop_ = NO_STOP;
    min_distance_ = -1;
    route_and_first_node_.clear();
    stop_and_node_.clear();
}

std::vector<StopID> Datastructures::all_stops()
{
    std::vector<StopID> stop_vector = {};
    if (stops_.size() > 0)
    {
        for (auto stop : stops_)
        {
            stop_vector.push_back(stop.first);
        }
    }
    return stop_vector;
}

bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    if (stops_.find(id) == stops_.end())
    {
        std::shared_ptr<Stop> stop(new Stop());
        stop->name = name;
        stop->coordinates = xy;
        stop->current_region = NO_REGION;
        stops_.insert({id, stop});
        stop_and_node_.insert({id, nullptr});
        stops_changed_ = true;
        coordinates_changed_ = true;
        // Jos minimi ja maksimi koordinaatit on annettu aiemmin, niin tarkistetaan uuden pysäkin suhde näihin
        if (min_distance_ != -1)
        {
            double distance = std::sqrt(pow(xy.x, 2) + pow(xy.y, 2));
            if (distance == min_distance_ && xy.y <= stops_[min_stop_]->coordinates.y)
            {
                min_distance_ = distance;
                min_stop_ = id;
            }
            else if (distance < min_distance_)
            {
                min_distance_ = distance;
                min_stop_ = id;
            }
        }
        if (max_distance_ != -1)
        {
            double distance = std::sqrt(pow(xy.x, 2) + pow(xy.y, 2));
            if (distance == max_distance_ && xy.y <= stops_[max_stop_]->coordinates.y)
            {
                max_distance_ = distance;
                max_stop_ = id;
            }
            else if (distance > max_distance_)
            {
                max_distance_ = distance;
                max_stop_ = id;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

Name Datastructures::get_stop_name(StopID id)
{
    if (stops_.find(id) != stops_.end())
    {
        return stops_[id]->name;
    }
    else
    {
        return NO_NAME;
    }
}

Coord Datastructures::get_stop_coord(StopID id)
{
    if (stops_.find(id) != stops_.end())
    {
        return stops_[id]->coordinates;
    }
    else
    {
        return NO_COORD;
    }
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    if (stops_changed_ == true)
    {
        stops_changed_ = false;
        std::multimap<Name,StopID> stop_map;
        std::vector<StopID> return_stops;
        return_stops.reserve(stops_.size());
        for (auto stop : stops_)
        {
            stop_map.insert({stop.second->name, stop.first});
        }
        for (auto stop : stop_map)
        {
            return_stops.push_back(stop.second);
        }
        stops_in_order_ = return_stops;
        return stops_in_order_;
    }
    else
    {
        return stops_in_order_;
    }
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    if (coordinates_changed_ == true)
    {
        std::multimap<double,StopID> stop_map;
        std::vector<StopID> return_stops = {};
        return_stops.reserve(stops_.size());
        for (auto stop : stops_)
        {
            Coord coordinate = stop.second->coordinates;
            double distance = std::sqrt(pow(coordinate.x, 2) + pow(coordinate.y, 2));
            stop_map.insert({distance,stop.first});
        }
        for (auto stop : stop_map)
        {
            return_stops.push_back(stop.second);
        }
        stops_in_coord_order_ = return_stops;
        return stops_in_coord_order_;
    }
    else
    {
        return stops_in_coord_order_;
    }
}

StopID Datastructures::min_coord()
{
    if (min_coord_changed_ == true)
    {
        int y;
        int counter = 0;
        double closest_distance;
        StopID return_stop = NO_STOP;
        for (auto stop : stops_)
        {
            Coord coordinate = stop.second->coordinates;
            double distance = std::sqrt(pow(coordinate.x, 2) + pow(coordinate.y, 2));
            if (counter == 0)
            {
                closest_distance = distance;
                min_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
                counter = 1;
            }
            else if (distance == closest_distance && coordinate.y <= y && counter == 1)
            {
                closest_distance = distance;
                min_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
            }
            else if (distance < min_distance_)
            {
                closest_distance = distance;
                min_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
            }
        }
        min_stop_ = return_stop;
        if (min_stop_ == NO_STOP)
        {
            min_coord_changed_ = true;
        }
        else
        {
            min_coord_changed_ = false;
        }
    }
    return min_stop_;
}

StopID Datastructures::max_coord()
{
    if (max_coord_changed_== true)
    {
        int y;
        int counter = 0;
        double farthest_distance;
        StopID return_stop = NO_STOP;
        for (auto stop : stops_)
        {
            Coord coordinate = stop.second->coordinates;
            double distance = std::sqrt(pow(coordinate.x, 2) + pow(coordinate.y, 2));
            if (counter == 0)
            {
                farthest_distance = distance;
                max_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
                counter = 1;
            }
            else if (distance == farthest_distance && coordinate.y <= y && counter == 1)
            {
                farthest_distance = distance;
                max_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
            }
            else if (distance > farthest_distance)
            {
                farthest_distance = distance;
                max_distance_ = distance;
                y = coordinate.y;
                return_stop = stop.first;
            }
        }
        max_stop_ = return_stop;
        if (max_stop_ == NO_STOP)
        {
            max_coord_changed_ = true;
        }
        else
        {
            max_coord_changed_ = false;
        }
    }
    return max_stop_;
}

std::vector<StopID> Datastructures::find_stops(Name const& name)
{
    std::vector<StopID> stop_vector;
    for (auto stop : stops_)
    {
        if (stop.second->name == name)
        {
            stop_vector.push_back(stop.first);
        }
    }
    return stop_vector;
}

bool Datastructures::change_stop_name(StopID id, const Name& newname)
{
    if (stops_.find(id) != stops_.end())
    {
        stops_[id]->name = newname;
        stops_changed_ = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool Datastructures::change_stop_coord(StopID id, Coord newcoord)
{
    if (stops_.find(id) != stops_.end())
    {
        stops_[id]->coordinates = newcoord;
        coordinates_changed_ = true;
        if (id == max_stop_)
        {
            max_stop_ = NO_STOP;
            max_coord_changed_ = true;
            max_distance_ = -1;
        }
        if (id == min_stop_)
        {
            min_stop_ = NO_STOP;
            min_coord_changed_ = true;
            min_distance_ = -1;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Datastructures::add_region(RegionID id, const Name &name)
{
    if (regions_.find(id) == regions_.end())
    {
        std::shared_ptr<Region> region(new Region());
        region->name = name;
        region->id = id;
        regions_.insert({id,region});
        return true;
    }
    else
    {
        return false;
    }
}

Name Datastructures::get_region_name(RegionID id)
{
    if (regions_.find(id) != regions_.end())
    {
        return regions_.at(id)->name;
    }
    else
    {
        return NO_NAME;
    }
}

std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> return_vector = {};
    for (auto region : regions_)
    {
        return_vector.push_back(region.first);
    }
    return return_vector;
}

bool Datastructures::add_stop_to_region(StopID id, RegionID parentid)
{
    if (stops_[id]->current_region == NO_REGION && stops_.find(id) != stops_.end() && regions_.find(parentid) != regions_.end())
    {
        stops_[id]->current_region = parentid;
        regions_[parentid]->stops.push_back(id);
        return true;
    }
    else
    {
        return false;
    }
}

bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if (regions_.find(id) != regions_.end() && regions_.find(parentid) != regions_.end() && regions_[id]->parent == nullptr)
    {
        regions_[id]->parent = regions_[parentid];
        regions_[parentid]->childrens.push_back(regions_[id]);
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<RegionID> Datastructures::stop_regions(StopID id)
{
    std::vector<RegionID> return_regions;
    if (stops_.find(id) != stops_.end() && stops_[id]->current_region != NO_REGION)
    {
        std::shared_ptr<Region> first_region = regions_[stops_[id]->current_region];
        while (first_region != nullptr)
        {
            return_regions.push_back(first_region->id);
            first_region = first_region->parent;
        }
        return return_regions;
    }
    else
    {
        return {NO_REGION};
    }
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // You don't have to use this method for anything, if you don't need it
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID id)
{
    Coord min_coordinates = NO_COORD;
    Coord max_coordinates = NO_COORD;
    if (regions_.find(id) != regions_.end())
    {
        std::pair<Coord, Coord> pair = {min_coordinates, max_coordinates};
        return find_min_and_max_coordinates(regions_[id], pair);
    }
    return {min_coordinates,max_coordinates};
}

std::vector<StopID> Datastructures::stops_closest_to(StopID id)
{
    std::vector<StopID> return_stops;
    if (stops_.find(id) != stops_.end())
    {
        std::vector<std::pair<std::pair<double, int>,StopID>> stops_and_distance;
        int x = stops_[id]->coordinates.x;
        int y = stops_[id]->coordinates.y;
        for (auto stop : stops_)
        {
            if (stop.first != id)
            {
                double distance = sqrt(pow(x-stop.second->coordinates.x, 2)+(pow(y-stop.second->coordinates.y, 2)));
                std::pair<std::pair<double, int>,StopID> pair = {{distance, stop.second->coordinates.y}, stop.first};
                stops_and_distance.push_back(pair);
            }
        }
        if (stops_and_distance.size() < 5)
        {
            std::sort(stops_and_distance.begin(), stops_and_distance.end());
        }
        else
        {
            std::partial_sort(stops_and_distance.begin(), stops_and_distance.begin() + 5, stops_and_distance.end());
        }
        for (long unsigned int counter = 0; counter < stops_and_distance.size(); ++counter)
        {
            if (counter == 5)
            {
                break;
            }
            else
            {
                return_stops.push_back(stops_and_distance.at(counter).second);
            }
        }
        return return_stops;
    }
    else
    {
        return {NO_STOP};
    }
}

bool Datastructures::remove_stop(StopID id)
{
    if (stops_.find(id) != stops_.end())
    {
        RegionID region = stops_[id]->current_region;
        if (region != NO_REGION)
        {
            for (auto stop : regions_[region]->stops)
            {
                if (stop == id)
                {
                    regions_[region]->stops.remove(id);
                    break;
                }
            }
        }
        if (id == min_stop_)
        {
            min_coord_changed_ = true;
            min_stop_ = NO_STOP;
            min_distance_ = -1;
        }
        if (id == max_stop_)
        {
            max_coord_changed_ = true;
            max_stop_ = NO_STOP;
            max_distance_ = -1;
        }
        stops_.erase(id);
        stops_changed_ = true;
        coordinates_changed_ = true;
        return true;
    }
    else
    {
        return false;
    }
}

RegionID Datastructures::stops_common_region(StopID id1, StopID id2)
{
    if (stops_.find(id1) != stops_.end() && stops_.find(id2) != stops_.end() && stops_[id1]->current_region != NO_REGION && stops_[id2]->current_region != NO_REGION)
    {
        std::shared_ptr<Region> id1_region = regions_[stops_[id1]->current_region];
        std::shared_ptr<Region> id2_region = regions_[stops_[id2]->current_region];
        std::vector<RegionID> id1_parents;
        std::vector<RegionID> id2_parents;
        id1_parents = find_regions(id1_region, id1_parents);
        id2_parents = find_regions(id2_region, id2_parents);
        for (auto region : id1_parents)
        {
            auto it = std::find(id2_parents.begin(), id2_parents.end(), region);
            if (it != id2_parents.end())
            {
                return region;
            }
        }
    }
    return NO_REGION;;
}

std::pair<Coord, Coord> Datastructures::find_min_and_max_coordinates(std::shared_ptr<Region> region, std::pair<Coord, Coord> both_coordinates)
{
    Coord min_coordinates = both_coordinates.first;
    Coord max_coordinates = both_coordinates.second;
    for (auto stop_id : region->stops)
    {
        Coord coordinate = stops_[stop_id]->coordinates;
        int x = coordinate.x;
        int y = coordinate.y;
        if (min_coordinates == NO_COORD && max_coordinates == NO_COORD)
        {
            min_coordinates = coordinate;
            max_coordinates = coordinate;
        }
        if (x < min_coordinates.x)
        {
            min_coordinates.x = x;
        }
        if (y < min_coordinates.y)
        {
            min_coordinates.y = y;
        }
        if (x > max_coordinates.x)
        {
            max_coordinates.x = x;
        }
        if (y > max_coordinates.y)
        {
            max_coordinates.y = y;
        }
    }
    both_coordinates.first = min_coordinates;
    both_coordinates.second = max_coordinates;
    for (auto next_region : region->childrens)
    {
        both_coordinates = find_min_and_max_coordinates(next_region, both_coordinates);
    }
    return both_coordinates;
}

std::vector<RegionID> Datastructures::find_regions(std::shared_ptr<Region> region, std::vector<RegionID> parent_vector)
{
    if (region != nullptr)
    {
        parent_vector.push_back(region->id);
        parent_vector = find_regions(region->parent, parent_vector);
    }
    return parent_vector;
}

std::vector<RouteID> Datastructures::all_routes()
{
    std::vector<RouteID> routes = {};
    if (route_and_first_node_.size() > 0)
    {
        for (auto route : route_and_first_node_)
        {
            routes.push_back(route.first);
        }

    }
    return routes;
}

bool Datastructures::add_route(RouteID id, std::vector<StopID> stops)
{
    if (stops.size() > 1 && route_and_first_node_.find(id) == route_and_first_node_.end())
    {
        for (auto stop : stops)
        {
            if (stops_.find(stop) == stops_.end())
            {
                return false;
            }
        }
        int counter = 0;
        std::shared_ptr<Node> previous_node;
        for (auto stop : stops)
        {
            if (stop_and_node_[stop] == nullptr)
            {
                std::shared_ptr<Node> node = std::make_shared<Node>();
                node->stopid = stop;
                node->routes_and_next_stop.insert({id, nullptr});
                stop_and_node_[stop] = node;
                if (counter == 0)
                {
                    route_and_first_node_.insert({id, node});
                    counter = 1;
                }
                else
                {
                    previous_node->routes_and_next_stop[id] = node;
                }
                previous_node = node;
            }
            else
            {
                std::shared_ptr<Node> node = stop_and_node_[stop];
                node->routes_and_next_stop.insert({id, nullptr});
                if (counter == 0)
                {
                    route_and_first_node_.insert({id, node});
                    counter = 1;
                }
                else
                {
                    previous_node->routes_and_next_stop[id] = node;
                }
                previous_node = node;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::pair<RouteID, StopID>> Datastructures::routes_from(StopID stopid)
{
    if (stops_.find(stopid) != stops_.end())
    {
        std::vector<std::pair<RouteID, StopID>> route_and_stop = {};
        std::shared_ptr<Node> node = stop_and_node_[stopid];
        if (node != nullptr)
        {
            for (auto next_node : node->routes_and_next_stop)
            {
                if (next_node.second != nullptr)
                {
                    route_and_stop.push_back({next_node.first, next_node.second->stopid});
                }
            }
            std::pair<RouteID, std::vector<StopID>> walking_connections = node->walking_connections;
            if (walking_connections.second.size() > 0)
            {
                for (auto stop : walking_connections.second)
                {
                    route_and_stop.push_back({walking_connections.first, stop});
                }
            }
        }
        return route_and_stop;
    }
    else
    {
        return {{NO_ROUTE, NO_STOP}};
    }
}

std::vector<StopID> Datastructures::route_stops(RouteID id)
{
    if (route_and_first_node_.find(id) != route_and_first_node_.end())
    {
        std::vector<StopID> return_stops = {};
        std::shared_ptr<Node> first_node = route_and_first_node_[id];
        while (first_node != nullptr)
        {
            return_stops.push_back(first_node->stopid);
            first_node = first_node->routes_and_next_stop[id];
        }
        return return_stops;
    }
    else
    {
        return {NO_STOP};
    }
}

void Datastructures::clear_routes()
{
    route_and_first_node_.clear();
    stop_and_node_.clear();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_any(StopID fromstop, StopID tostop)
{
    if (stops_.find(fromstop) != stops_.end() && stops_.find(tostop) != stops_.end())
    {
        std::vector<std::tuple<StopID, RouteID, Distance>> return_vector;
        // Alustetaan solmut
        for (auto node : stop_and_node_)
        {
            std::shared_ptr<Node> node1 = node.second;
            if (node1 != nullptr)
            {
                node1->color = WHITE;
                node1->previous_node.first = nullptr;
                node1->previous_node.second = NO_ROUTE;
                node1->distance = std::numeric_limits<int>::max();
            }
        }
        std::stack<std::shared_ptr<Node>> nodes;
        std::shared_ptr<Node> node = stop_and_node_[fromstop];
        if (node != nullptr)
        {
            nodes.push(node);
            std::shared_ptr<Node> last_node = nullptr;
            while (nodes.size() > 0)
            {
                std::shared_ptr<Node> node = nodes.top();
                nodes.pop();
                if (node->color == WHITE)
                {
                    std::shared_ptr<Node> previous_node = node->previous_node.first;
                    if (previous_node != nullptr)
                    {
                        node->distance = sqrt(pow(stops_[previous_node->stopid]->coordinates.x - stops_[node->stopid]->coordinates.x, 2)
                                + pow(stops_[previous_node->stopid]->coordinates.y - stops_[node->stopid]->coordinates.y, 2)) + previous_node->distance;
                    }
                    // Merkitään lähtösolmun etäisyys nollaksi
                    else
                    {
                        node->distance = 0;
                    }
                    if (node->stopid == tostop)
                    {
                        last_node = node;
                        break;
                    }
                    node->color = GRAY;
                    nodes.push(node);
                    for (auto neighbour : node->routes_and_next_stop)
                    {
                        std::shared_ptr<Node> neighbour_node = neighbour.second;
                        if (neighbour_node != nullptr)
                        {
                            if (neighbour_node->color == WHITE)
                            {
                                neighbour_node->previous_node.first = node;
                                nodes.push(neighbour_node);
                            }
                        }
                    }
                }
                else
                {
                    node->color = BLACK;
                }
            }
            if (last_node != nullptr)
            {
                return_vector = printer(last_node, fromstop, return_vector, NO_ROUTE);
            }
        }
        return return_vector;
    }
    else
    {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }
}

std::vector<std::tuple<StopID, RouteID, Distance> > Datastructures::printer(std::shared_ptr<Datastructures::Node> last_node, StopID fromstop, std::vector<std::tuple<StopID, RouteID, Distance>> return_vector, RouteID route)
{
    if (last_node->stopid == fromstop)
    {
        return_vector.push_back({last_node->stopid, route, last_node->distance});
    }
    else
    {
        return_vector = printer(last_node->previous_node.first, fromstop, return_vector, last_node->previous_node.second);
        return_vector.push_back({last_node->stopid, route, last_node->distance});
    }
    return return_vector;
}


std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_least_stops(StopID fromstop, StopID tostop)
{
    if (stops_.find(fromstop) != stops_.end() && stops_.find(tostop) != stops_.end())
    {
        std::vector<std::tuple<StopID, RouteID, Distance>> return_vector;
        // Alustetaan solmut
        for (auto node : stop_and_node_)
        {
            std::shared_ptr<Node> node1 = node.second;
            if (node1 != nullptr)
            {
                node1->color = WHITE;
                node1->previous_node.first = nullptr;
                node1->previous_node.second = NO_ROUTE;
                node1->distance = std::numeric_limits<int>::max();
            }
        }
        std::queue<std::shared_ptr<Node>> nodes;
        std::shared_ptr<Node> node = stop_and_node_[fromstop];
        if (node != nullptr)
        {
            nodes.push(node);
            node->distance = 0;
            std::shared_ptr<Node> last_node = nullptr;
            while (nodes.size() > 0)
            {
                std::shared_ptr<Node> node = nodes.front();
                nodes.pop();
                for (auto neighbour : node->routes_and_next_stop)
                {
                    std::shared_ptr<Node> neighbour_node = neighbour.second;
                    if (neighbour_node != nullptr)
                    {
                        if (neighbour_node->color == WHITE)
                        {
                            neighbour_node->color = GRAY;
                            neighbour_node->previous_node.first = node;
                            neighbour_node->distance = sqrt(pow(stops_[node->stopid]->coordinates.x - stops_[neighbour_node->stopid]->coordinates.x, 2)
                                    + pow(stops_[node->stopid]->coordinates.y - stops_[neighbour_node->stopid]->coordinates.y, 2)) + node->distance;
                            neighbour_node->previous_node.second = neighbour.first;
                            if (neighbour_node->stopid == tostop)
                            {
                                last_node = neighbour_node;
                                break;
                            }
                            nodes.push(neighbour_node);
                        }
                    }
                }
                node->color = BLACK;
            }
            if (last_node != nullptr)
            {
                return_vector = printer(last_node, fromstop, return_vector, NO_ROUTE);
            }
        }
        return return_vector;
    }
    else
    {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_with_cycle(StopID fromstop)
{
    if (stops_.find(fromstop) != stops_.end())
    {
        std::vector<std::tuple<StopID, RouteID, Distance>> return_vector;
        std::tuple<StopID, RouteID, Distance> final_node;
        RouteID final_routeid;
        // Alustetaan solmut
        for (auto node : stop_and_node_)
        {
            std::shared_ptr<Node> node1 = node.second;
            if (node1 != nullptr)
            {
                node1->color = WHITE;
                node1->previous_node.first = nullptr;
                node1->previous_node.second = NO_ROUTE;
                node1->distance = std::numeric_limits<int>::max();
            }
        }
        std::stack<std::shared_ptr<Node>> nodes;
        std::shared_ptr<Node> node = stop_and_node_[fromstop];
        if (node != nullptr)
        {
            nodes.push(node);
            std::shared_ptr<Node> last_node = nullptr;
            while (nodes.size() > 0)
            {
                std::shared_ptr<Node> node = nodes.top();
                nodes.pop();
                if (node->color == WHITE)
                {
                    std::shared_ptr<Node> previous_node = node->previous_node.first;
                    if (previous_node != nullptr)
                    {
                        node->distance = sqrt(pow(stops_[previous_node->stopid]->coordinates.x - stops_[node->stopid]->coordinates.x, 2)
                                + pow(stops_[previous_node->stopid]->coordinates.y - stops_[node->stopid]->coordinates.y, 2)) + previous_node->distance;
                    }
                    // Merkitään lähtösolmun etäisyys nollaksi
                    else
                    {
                        node->distance = 0;
                    }
                    node->color = GRAY;
                    nodes.push(node);
                    for (auto neighbour : node->routes_and_next_stop)
                    {
                        std::shared_ptr<Node> neighbour_node = neighbour.second;
                        if (neighbour_node != nullptr)
                        {
                            if (neighbour_node->color == WHITE)
                            {
                                neighbour_node->previous_node.first = node;
                                neighbour_node->previous_node.second = neighbour.first;
                                nodes.push(neighbour_node);
                            }
                            else if (neighbour_node->color == GRAY)
                            {
                                last_node = node;
                                final_routeid = neighbour.first;
                                int distance = sqrt(pow(stops_[neighbour_node->stopid]->coordinates.x - stops_[node->stopid]->coordinates.x, 2)
                                        + pow(stops_[neighbour_node->stopid]->coordinates.y - stops_[node->stopid]->coordinates.y, 2)) + node->distance;
                                final_node = {neighbour_node->stopid, NO_ROUTE, distance};
                                break;
                            }
                        }
                    }
                }
                else
                {
                    node->color = BLACK;
                }
            }
            if (last_node != nullptr)
            {
                return_vector = printer(last_node, fromstop, return_vector, final_routeid);
                return_vector.push_back(final_node);
            }
        }
        return return_vector;
    }
    else
    {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_shortest_distance(StopID fromstop, StopID tostop)
{
    if (stops_.find(fromstop) != stops_.end() && stops_.find(tostop) != stops_.end())
    {
        std::vector<std::tuple<StopID, RouteID, Distance>> return_vector;
        // Alustetaan solmut
        for (auto node : stop_and_node_)
        {
            std::shared_ptr<Node> node1 = node.second;
            if (node1 != nullptr)
            {
                node1->color = WHITE;
                node1->previous_node.first = nullptr;
                node1->previous_node.second = NO_ROUTE;
                node1->distance = std::numeric_limits<int>::max();
            }
        }
        std::priority_queue<std::pair<int, std::shared_ptr<Node>>> nodes;
        std::shared_ptr<Node> node = stop_and_node_[fromstop];
        if (node != nullptr)
        {
            node->distance = 0;
            nodes.push({0, node});
            node->color = GRAY;
            std::shared_ptr<Node> last_node = nullptr;
            while (nodes.size() > 0)
            {
                std::pair<int, std::shared_ptr<Node>> node = nodes.top();
                nodes.pop();
                if (node.second->stopid == tostop)
                {
                    last_node = node.second;
                    break;
                }
                // Varmistetaan, että jo käsiteltyjä solmuja ei käsitellä uudelleen
                else if (node.second->color != BLACK)
                {
                    for (auto neighbour : node.second->routes_and_next_stop)
                    {
                        std::shared_ptr<Node> neighbour_node = neighbour.second;
                        if (neighbour_node != nullptr)
                        {
                            int distance = sqrt(pow(stops_[neighbour_node->stopid]->coordinates.x - stops_[node.second->stopid]->coordinates.x, 2)
                                    + pow(stops_[neighbour_node->stopid]->coordinates.y - stops_[node.second->stopid]->coordinates.y, 2)) + node.second->distance;
                            if (neighbour_node->color == WHITE)
                            {
                                neighbour_node->color = GRAY;
                                nodes.push({distance * -1, neighbour_node});
                            }
                            if (distance <= neighbour_node->distance)
                            {
                                neighbour_node->distance = distance;
                                neighbour_node->previous_node.first = node.second;
                                neighbour_node->previous_node.second = neighbour.first;
                                nodes.push({distance * -1, neighbour_node});
                            }
                        }
                    }
                    node.second->color = BLACK;
                }
            }
            if (last_node != nullptr)
            {
                return_vector = printer(last_node, fromstop, return_vector, NO_ROUTE);
            }

        }
        return return_vector;
    }
    else
    {
        return {{NO_STOP, NO_ROUTE, NO_DISTANCE}};
    }
}

bool Datastructures::add_trip(RouteID routeid, std::vector<Time> const& stop_times)
{
    if (route_and_first_node_.find(routeid) != route_and_first_node_.end())
    {
        std::shared_ptr<Node> node = route_and_first_node_[routeid];
        int index = 0;
        while (node != nullptr)
        {
            node->route_and_times.insert({routeid, stop_times.at(index)});
            node = node->routes_and_next_stop[routeid];
            ++index;
        }
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::pair<Time, Duration>> Datastructures::route_times_from(RouteID routeid, StopID stopid)
{
    if (route_and_first_node_.find(routeid) != route_and_first_node_.end() && stops_.find(stopid) != stops_.end() && stop_and_node_[stopid]->route_and_times.find(routeid) != stop_and_node_[stopid]->route_and_times.end())
    {
        std::vector<std::pair<Time, Duration>> return_vector;
        std::vector<Time> times;
        std::shared_ptr<Node> node = stop_and_node_[stopid];
        std::shared_ptr<Node> next_node = node->routes_and_next_stop[routeid];
        auto range = node->route_and_times.equal_range(routeid);
        for (auto i = range.first; i != range.second; ++i)
        {
            times.push_back(i->second);
        }
        range = next_node->route_and_times.equal_range(routeid);
        int index = 0;
        for (auto i = range.first; i != range.second; ++i)
        {
            Duration duration = i->second - times.at(index);
            return_vector.push_back({times.at(index), duration});
            ++index;
        }
        return return_vector;
    }
    return {{NO_TIME, NO_DURATION}};
}

std::vector<std::tuple<StopID, RouteID, Time> > Datastructures::journey_earliest_arrival(StopID fromstop, StopID tostop, Time starttime)
{
    if (stops_.find(fromstop) != stops_.end() && stops_.find(tostop) != stops_.end())
    {
        std::vector<std::tuple<StopID, RouteID, Time>> return_vector;
        // Alustetaan solmut
        for (auto node : stop_and_node_)
        {
            std::shared_ptr<Node> node1 = node.second;
            if (node1 != nullptr)
            {
                node1->color = WHITE;
                node1->previous_node.first = nullptr;
                node1->previous_node.second = NO_ROUTE;
                node1->distance = std::numeric_limits<int>::max();
                node1->time = std::numeric_limits<int>::max();
                node1->duration = std::numeric_limits<int>::max();
                node1->route_ends = false;
            }
        }
        std::priority_queue<std::pair<Duration, std::shared_ptr<Node>>> nodes;
        std::shared_ptr<Node> node1 = stop_and_node_[fromstop];
        if (node1 != nullptr)
        {
            // Otetaan ensimmäisen bussin lähtöaika, joka on lähimpänä starttimee
            for (auto node : node1->route_and_times)
            {
                Time time = node.second;
                Duration start_time_tester = time - starttime;
                if (start_time_tester >= 0 && time < node1->time)
                {
                    node1->time = time;
                }
            }
            node1->duration = 0;
            node1->color = GRAY;
            nodes.push({0, node1});
            std::shared_ptr<Node> last_node = nullptr;
            while (nodes.size() > 0)
            {
                std::pair<Duration, std::shared_ptr<Node>> node = nodes.top();
                nodes.pop();
                std::shared_ptr<Node> node_second = node.second;
                if (node_second->stopid == tostop)
                {
                    last_node = node_second;
                    break;
                }
                // Varmistetaan, että ei käsitellä jo käsiteltyjä solmuja
                else if (node_second->color != BLACK)
                {
                    for (auto neighbour : node_second->routes_and_next_stop)
                    {
                        std::shared_ptr<Node> neighbour_node = neighbour.second;
                        if (neighbour_node != nullptr)
                        {
                            Duration duration;
                            // Jos reitti vaihtuu solmussa, niin valitaan uuden reitin aika, joka on lähimpänä edellisen reitin aikaa
                            if (node_second->route_ends == true)
                            {
                                node_second->duration = std::numeric_limits<int>::max();
                                auto range = node_second->route_and_times.equal_range(neighbour.first);
                                Time arrival_time = node_second->time;
                                for (auto i = range.first; i != range.second; ++i)
                                {
                                    duration = i->second - arrival_time;
                                    if (duration <= node_second->duration && duration >= 0)
                                    {
                                        node_second->duration = duration;
                                        node_second->time = i->second;
                                    }
                                }
                            }
                            auto range = neighbour_node->route_and_times.equal_range(neighbour.first);
                            for (auto i = range.first; i != range.second; ++i)
                            {
                                duration = i->second - node_second->time;
                                if (duration <= neighbour_node->duration && duration > 0)
                                {
                                    if (neighbour_node->routes_and_next_stop[neighbour.first] == nullptr)
                                    {
                                        neighbour_node->route_ends = true;
                                    }
                                    neighbour_node->duration = duration;
                                    neighbour_node->previous_node.first = node_second;
                                    neighbour_node->previous_node.second = neighbour.first;
                                    neighbour_node->time = i->second;
                                }
                            }
                            if (neighbour_node->color == WHITE && duration > 0)
                            {
                                neighbour_node->color = GRAY;
                                nodes.push({neighbour_node->duration * -1, neighbour_node});
                            }
                        }
                    }
                    node_second->color = BLACK;
                }
            }
            if (last_node != nullptr)
            {
                return_vector = time_printer(last_node, fromstop, return_vector, NO_ROUTE);
            }
        }
        return return_vector;
    }
    else
    {
        return {{NO_STOP, NO_ROUTE, NO_TIME}};
    }
}

std::vector<std::tuple<StopID, RouteID, Time> > Datastructures::time_printer(std::shared_ptr<Datastructures::Node> last_node, StopID fromstop, std::vector<std::tuple<StopID, RouteID, Time> > return_vector, RouteID route)
{
    if (last_node->stopid == fromstop)
    {
        return_vector.push_back({last_node->stopid, route, last_node->time});
    }
    else
    {
        return_vector = time_printer(last_node->previous_node.first, fromstop, return_vector, last_node->previous_node.second);
        return_vector.push_back({last_node->stopid, route, last_node->time});
    }
    return return_vector;
}

void Datastructures::add_walking_connections()
{
    for (auto stop : stop_and_node_)
    {
        if (stop.second == nullptr)
        {
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->stopid = stop.first;
            node->walking_connections.second = stops_closest_to(stop.first);
            stop.second = node;
        }
        else
        {
            stop.second->walking_connections.second = stops_closest_to(stop.first);
        }
    }
}
