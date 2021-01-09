// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <unordered_map>
#include <memory>
#include <map>
#include <list>

// Types for IDs
using StopID = long int;
using RegionID = std::string;
using RouteID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
RouteID const NO_ROUTE = "!!NO_ROUTE!!";
StopID const NO_STOP = -1;
RegionID const NO_REGION = "!!NO_REGION!!";
int const WHITE = 2;
int const BLACK = 0;
int const GRAY = 1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for time of day in minutes from midnight (i.e., 60*hours + minutes)
using Time = int;

// Return value for cases where color was not found
Time const NO_TIME = std::numeric_limits<Time>::min();

// Type for a duration of time (in minutes)
using Duration = int;

// Return value for cases where Duration is unknown
Duration const NO_DURATION = NO_VALUE;

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    int stop_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> all_stops();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_stop(StopID id, Name const& name, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_stop_name(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_stop_coord(StopID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> stops_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> stops_coord_order();

    // Estimate of performance:
    // Short rationale for estimate:
    StopID min_coord();

    // Estimate of performance:
    // Short rationale for estimate:
    StopID max_coord();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StopID> find_stops(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_stop_name(StopID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_stop_coord(StopID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_region(RegionID id, Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_region_name(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_regions();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_stop_to_region(StopID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> stop_regions(StopID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance:
    // Short rationale for estimate:
    std::pair<Coord, Coord> region_bounding_box(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Koska joudutaan käymään kaikki pysäkit läpi
    std::vector<StopID> stops_closest_to(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_stop(StopID id);

    // Estimate of performance:
    // Short rationale for estimate:
    RegionID stops_common_region(StopID id1, StopID id2);

    // Phase 2 operations

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska käydään kaikki reitit läpi ja jos ei reittejä niin vakioaikainen
    std::vector<RouteID> all_routes();

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska käydään kaikki reitit läpi sekä [] operaatio on tätä tasoa. Jos ensimmäinen if on false, niin keskimäärin vakioaikainen
    bool add_route(RouteID id, std::vector<StopID> stops);

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska käydään läpi kaikki pysäkinreitit ja jos eka if on false, niin keskimäärin vakioaikainen
    std::vector<std::pair<RouteID, StopID>> routes_from(StopID stopid);

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska käydään reitin kaikki pysäkit läpi ja jos eka if on false, niin keskimäärin vakioaikainen
    std::vector<StopID> route_stops(RouteID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Koska operaatio .clear() on tätä tehokkuutta
    void clear_routes();

    // Estimate of performance:O(V+E), missä V on solmujen ja E kaarien määrä. Parhaassa tapauksessa vakioaikainen. Huom. tehokkuuteen vaikuttaa myös printer-funktion tehokkuus, joka on tehokkuudeltaan O(n)
    // Short rationale for estimate: Koska kyseessä on syvyyten ensin -hausta. Keskimäärin vakioaikainen, jos ensimmäinen if on false
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_any(StopID fromstop, StopID tostop);

//    // Non-compulsory operations

    // Estimate of performance:O(V+E), missä V on solmujen ja E kaarien määrä. Parhaassa tapauksessa vakioaikainen. Huom. tehokkuuteen vaikuttaa myös printer-funktion tehokkuus, joka on tehokkuudeltaan O(n)
    // Short rationale for estimate: Koska kyseessä on leveyteen ensin -hausta. Keskimäärin vakioaikainen, jos ensimmäinen if on false
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_least_stops(StopID fromstop, StopID tostop);

    // Estimate of performance:O(V+E), missä V on solmujen ja E kaarien määrä. Parhaassa tapauksessa vakioaikainen. Huom. tehokkuuteen vaikuttaa myös printer-funktion tehokkuus, joka on tehokkuudeltaan O(n)
    // Short rationale for estimate: Koska kyseessä on syvyyten ensin -hausta. Keskimäärin vakioaikainen, jos ensimmäinen if on false
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_with_cycle(StopID fromstop);

    // Estimate of performance:O(V+E), missä V on solmujen ja E kaarien määrä. Parhaassa tapauksessa vakioaikainen. Huom. tehokkuuteen vaikuttaa myös printer-funktion tehokkuus, joka on tehokkuudeltaan O(n)
    // Short rationale for estimate: Koska kyseessä on syvyyten ensin -hausta. Keskimäärin vakioaikainen, jos ensimmäinen if on false
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_shortest_distance(StopID fromstop, StopID tostop);

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska käydään kaikki sille annettavat ajat läpi ja []-operaatio on tätä luokkaa huonoimmassa tapauksessa. Vakioaikainen keskimäärin, jos ensimmäinen if on false
    bool add_trip(RouteID routeid, const std::vector<Time> &stop_times);

    // Estimate of performance: O(n), parhaassa tapauksessa vakioaikainen
    // Short rationale for estimate: Koska equal_range() on tätä luokkaa ja käydään kaikki reitin ajat läpi. Jos ensimmäinen if on false, niin keskimäärin vakioaikainen.
    std::vector<std::pair<Time, Duration> > route_times_from(RouteID routeid, StopID stopid);

    // Estimate of performance: O(n²), parhaassa tapauksessa vakioaikainen. Huom. tehokkuuteen vaikuttaa myös time_printer-funktio, joka on tehokkuudeltaan O(n)
    // Short rationale for estimate: Tupla for-silmukka aiheuttaa huonon tehokkuuden. Jos ensimmäinen if false, niin keskimäärin vakioaikainen.
    std::vector<std::tuple<StopID, RouteID, Time>> journey_earliest_arrival(StopID fromstop, StopID tostop, Time starttime);

    // Estimate of performance: O(N²)
    // Short rationale for estimate: Koska joudutaan käymään kaikki pysäkit läpi, sekä stops_closest_to-funktio on O(n) tehokkuutta
    void add_walking_connections(); // Note! This method is completely optional, and not part of any testing

private:
    // Ensimmäisen osion private
    struct Stop
    {
        Name name;
        Coord coordinates;
        RegionID current_region;
    };

    struct Region
    {
        Name name;
        RegionID id;
        std::list<StopID> stops = {};
        std::list<std::shared_ptr<Region>> childrens = {};
        std::shared_ptr<Region> parent = nullptr;
    };
    std::unordered_map<StopID, std::shared_ptr<Stop>> stops_ = {};
    std::unordered_map<RegionID, std::shared_ptr<Region>> regions_ = {};
    std::pair<Coord,Coord> find_min_and_max_coordinates(std::shared_ptr<Region> region, std::pair<Coord, Coord> both_coordinates);
    std::vector<RegionID> find_regions(std::shared_ptr<Region> region, std::vector<RegionID> parent_vector);
    bool stops_changed_ = false;
    bool coordinates_changed_ = false;
    bool max_coord_changed_ = true;
    bool min_coord_changed_ = true;
    std::vector<StopID> stops_in_order_ = {};
    std::vector<StopID> stops_in_coord_order_ = {};
    StopID max_stop_ = NO_STOP;
    StopID min_stop_ = NO_STOP;
    double max_distance_ = -1;
    double min_distance_ = -1;
    // toisen osion private
    struct Node
    {
        StopID stopid;
        std::unordered_map<RouteID, std::shared_ptr<Node>> routes_and_next_stop = {};
        std::pair<std::shared_ptr<Node>, RouteID> previous_node = {};
        std::multimap<RouteID, Time> route_and_times = {};
        std::pair<RouteID, std::vector<StopID>> walking_connections = {NO_ROUTE, {}};
        int color = WHITE;
        int route_ends = false;
        int distance = std::numeric_limits<int>::max();
        Time time = std::numeric_limits<int>::max();
        Duration duration = std::numeric_limits<int>::max();
    };
    std::unordered_map<RouteID, std::shared_ptr<Node>> route_and_first_node_ = {};
    std::unordered_map<StopID, std::shared_ptr<Node>> stop_and_node_ = {};
    // Estimate of performance: O(n)
    // Short rationale for estimate: Koska käydään läpi kaikki reitin solmut
    std::vector<std::tuple<StopID, RouteID, Distance>> printer(std::shared_ptr<Node> last_node, StopID fromstop, std::vector<std::tuple<StopID, RouteID, Distance>> return_vector, RouteID route);
    // Estimate of performance: O(n)
    // Short rationale for estimate: Koska käydään läpi kaikki reitin solmut
    std::vector<std::tuple<StopID, RouteID, Time>> time_printer(std::shared_ptr<Node> last_node, StopID fromstop, std::vector<std::tuple<StopID, RouteID, Time>> return_vector, RouteID route);
};

#endif // DATASTRUCTURES_HH
