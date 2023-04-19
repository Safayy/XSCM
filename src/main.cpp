#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

struct Location {
    double lat;
    double lon;
    string name;
};

double calcDistance(Location loc1, Location loc2) {
    const double earthRadius = 6371; // km
    double dLat = (loc2.lat - loc1.lat) * M_PI / 180;
    double dLon = (loc2.lon - loc1.lon) * M_PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) + cos(loc1.lat * M_PI / 180) * cos(loc2.lat * M_PI / 180) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = earthRadius * c;
    return d;
}

vector<int> findOptimalRoute(vector<Location> retailers, Location supplier, double& totalDistance, vector<double>& retailerDistances) {
    int numRetailers = retailers.size();
    vector<bool> visited(numRetailers, false);
    vector<int> optimalRoute(numRetailers+1);
    optimalRoute[0] = 0;
    visited[0] = true;

    for (int i = 1; i < numRetailers; i++) {
        double minDistance = INFINITY;
        int nearestNeighbor = -1;
        for (int j = 0; j < numRetailers; j++) {
            if (!visited[j]) {
                double distance = calcDistance(retailers[optimalRoute[i-1]], retailers[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbor = j;
                }
            }
        }
        optimalRoute[i] = nearestNeighbor;
        visited[nearestNeighbor] = true;
    }
    optimalRoute[numRetailers] = 0;

    double distance = calcDistance(supplier, retailers[optimalRoute[0]]);
    retailerDistances.clear();
    for (int i = 0; i < numRetailers-1; i++) {
        distance += calcDistance(retailers[optimalRoute[i]], retailers[optimalRoute[i+1]]);
        retailerDistances.push_back(calcDistance(retailers[optimalRoute[i]], retailers[optimalRoute[i+1]]));
    }
    distance += calcDistance(retailers[optimalRoute[numRetailers-1]], supplier);
totalDistance = distance;
retailerDistances.push_back(calcDistance(retailers[optimalRoute[numRetailers-1]], supplier));
return optimalRoute;

}

void printRoute(vector<Location> locations, vector<int> route, double totalDistance, vector<double> retailerDistances) {
cout << "Optimal route:" << endl;
for (int i = 0; i < route.size(); i++) {
cout << locations[route[i]].name << " ";
}
cout << endl;
cout << "Total distance traveled: " << totalDistance << " km" << endl;
cout << "Retailer distances:" << endl;
for (int i = 0; i < retailerDistances.size(); i++) {
cout << locations[route[i]].name << " to " << locations[route[i+1]].name << ": " << retailerDistances[i] << " km" << endl;
}
}

int main() {
    Location supplier = {40.748817, -73.985428, "Supplier"};
    vector<Location> retailers = {
        {40.760399, -73.991247, "Retailer 1"},
        {40.752726, -73.996611, "Retailer 2"},
        {40.759901, -73.984474, "Retailer 3"},
        {40.752086, -73.982792, "Retailer 4"},
        {40.755647, -73.986791, "Retailer 5"}
    };

    cout << "Unoptimized Route:\t";
    cout << supplier.name << " -> ";
    for (int i = 0; i < retailers.size(); i++) {
        cout << retailers[i].name << " -> ";
    }
    cout << supplier.name << endl;

    double totalDistance;
    vector<double> retailerDistances;
    vector<int> optimalRoute = findOptimalRoute(retailers, supplier, totalDistance, retailerDistances);

    cout << endl;
    cout << "Optimal Route:\t\t" ;
    cout << supplier.name << " -> ";
    for (int i = 0; i < optimalRoute.size()-1; i++) {
        cout << retailers[optimalRoute[i]].name << " -> ";
    }
    cout << supplier.name << endl;

    cout << endl;

    return 0;
}