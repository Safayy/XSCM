#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

// Define a struct for storing the latitude and longitude of a location
struct Location {
    double lat;
    double lon;
};

// Define a function for calculating the distance between two locations using the haversine formula
double calcDistance(Location loc1, Location loc2) {
    const double earthRadius = 6371; // km
    double dLat = (loc2.lat - loc1.lat) * M_PI / 180;
    double dLon = (loc2.lon - loc1.lon) * M_PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) + cos(loc1.lat * M_PI / 180) * cos(loc2.lat * M_PI / 180) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = earthRadius * c;
    return d;
}

// Define a function for finding the optimal route for visiting all retailers and the supplier
vector<int> findOptimalRoute(vector<Location> retailers, Location supplier, double& totalDistance, vector<double>& retailerDistances) {
    vector<int> route;
    for (vector<Location>::size_type i = 0; i < retailers.size(); i++) {
        route.push_back(i);
    }

    double minDistance = INFINITY;

    do {
        double distance = calcDistance(supplier, retailers[route[0]]);
        for (vector<int>::size_type i = 0; i < route.size() - 1; i++) {
            distance += calcDistance(retailers[route[i]], retailers[route[i+1]]);
        }
        distance += calcDistance(retailers[route[route.size()-1]], supplier);

        if (distance < minDistance) {
            minDistance = distance;
            retailerDistances.clear();
            for (vector<int>::size_type i = 0; i < route.size() - 1; i++) {
                retailerDistances.push_back(calcDistance(retailers[route[i]], retailers[route[i+1]]));
            }
            totalDistance = distance;
        }
    } while (next_permutation(route.begin(), route.end()));

    return route;
}

// Define a function for finding the unoptimized route given the locations of retailers and supplier
vector<int> findUnoptimizedRoute(vector<Location> retailers, Location supplier, double& totalDistance, vector<double>& retailerDistances) {
    vector<int> route;
    for (vector<Location>::size_type i = 0; i < retailers.size(); i++) {
        route.push_back(i);
    }

    double distance = calcDistance(supplier, retailers[route[0]]);
    for (vector<int>::size_type i = 0; i < route.size() - 1; i++) {
        distance += calcDistance(retailers[route[i]], retailers[route[i+1]]);
    }
    distance += calcDistance(retailers[route[route.size()-1]], supplier);

    totalDistance = distance;

    retailerDistances.clear();
    for (vector<int>::size_type i = 0; i < route.size() - 1; i++) {
        retailerDistances.push_back(calcDistance(retailers[route[i]], retailers[route[i+1]]));
    }

    return route;
}


// Define a function for printing the optimal route
// Define a function for printing the routes
void printRoute(vector<Location> retailers, Location supplier, vector<int> unoptimizedRoute, vector<int> optimizedRoute) {
    cout << "Unoptimized route: Supplier -> ";
    for (vector<int>::size_type i = 0; i < unoptimizedRoute.size(); i++) {
        cout << "(" << retailers[unoptimizedRoute[i]].lat << ", " << retailers[unoptimizedRoute[i]].lon << ") -> ";
    }
    cout << "Supplier" << endl;

    cout << "Optimized route: Supplier -> ";
    for (vector<int>::size_type i = 0; i < optimizedRoute.size(); i++) {
        cout << "(" << retailers[optimizedRoute[i]].lat << ", " << retailers[optimizedRoute[i]].lon << ") -> ";
    }
    cout << "Supplier" << endl;
}

int main() {
    // Define the locations of the retailers and supplier
    vector<Location> retailers = {{40.7282, -73.7949}, {40.7436, -73.9117}, {40.6859, -73.9742}, {40.7736, -73.9826}};
    Location supplier = {40.6939, -73.9852};


    // Find the unoptimized route
    double unoptimizedDistance = 0;
    vector<double> unoptimizedRetailerDistances;
    vector<int> unoptimizedRoute = findUnoptimizedRoute(retailers, supplier, unoptimizedDistance, unoptimizedRetailerDistances);

    // Print the unoptimized route
    // printRoute(retailers, supplier, unoptimizedRoute, "Unoptimized");
    // Print the routes
   


    // Find the optimized route
    double optimizedDistance = 0;
    vector<double> optimizedRetailerDistances;
    vector<int> optimizedRoute = findOptimalRoute(retailers, supplier, optimizedDistance, optimizedRetailerDistances);

    // Print the optimized route
    // printRoute(retailers, supplier, optimizedRoute, "Optimized");

    // Print the distance traveled for each route
    cout << "Unoptimized distance: " << unoptimizedDistance << " km" << endl;
    cout << "Optimized distance: " << optimizedDistance << " km" << endl;

    // Print the distance traveled for each retailer in the optimized route
    cout << "Retailer distances (in km): ";
    for (double distance : optimizedRetailerDistances) {
        cout << distance << " ";
    }
    cout << endl;

    //  cout << endl;
    printRoute(retailers, supplier, unoptimizedRoute, optimizedRoute);

    return 0;
}
