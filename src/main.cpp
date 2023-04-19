#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Define a struct to represent a location (supplier or retailer)
struct Location {
    string name;
    double latitude;
    double longitude;
    double costOfGoods; // added cost of goods
};

// Define a function for calculating the distance between two locations using the haversine formula
double calcDistance(Location loc1, Location loc2) {
    const double R = 6371; // Radius of the earth in km
    double lat1 = loc1.latitude * M_PI / 180.0;
    double lon1 = loc1.longitude * M_PI / 180.0;
    double lat2 = loc2.latitude * M_PI / 180.0;
    double lon2 = loc2.longitude * M_PI / 180.0;
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = R * c;
    return distance;
}

// Define a function for finding the optimal route
vector<int> findOptimalRoute(vector<Location> retailers, Location supplier, double& totalDistance, vector<double>& retailerDistances) {
    int numRetailers = retailers.size();
    vector<bool> visited(numRetailers, false); // Keep track of which retailers have been visited
    vector<int> optimalRoute(numRetailers+1); // The optimal route will be of length numRetailers+1 (visiting all retailers and returning to the supplier)
    optimalRoute[0] = 0; // Start at the supplier
    visited[0] = true;

    // Find the nearest neighbor of the current location and add it to the route
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
    optimalRoute[numRetailers] = 0; // Return to the supplier

    // Calculate the total distance and retailer distances for the optimal route
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

// Define a function for printing the optimal route and the distance traveled
void printOptimalRoute(vector<Location> retailers, Location supplier, double totalDistance, vector<int> optimalRoute, vector<double> retailerDistances) {
cout << "Optimal route:" << endl;
cout << supplier.name << " -> ";
for (int i = 0; i < optimalRoute.size()-1; i++) {
cout << retailers[optimalRoute[i]].name << " -> ";
}
cout << supplier.name << endl;
cout << "Total distance traveled: " << totalDistance << " km" << endl;
double costOfGoods = 0;
for (int i = 0; i < optimalRoute.size(); i++) {
    costOfGoods += retailers[optimalRoute[i]].costOfGoods;
}

double gasCost = totalDistance * 0.1; // assuming gas cost of 0.1 dollar per km
double wageCost = totalDistance * 15; // assuming wage of 15 dollars per km
double profit = costOfGoods - gasCost - wageCost;
cout << "Total cost of goods: " << costOfGoods << " dollars" << endl;
cout << "Total gas cost: " << gasCost << " dollars" << endl;
cout << "Total wage cost: " << wageCost << " dollars" << endl;
cout << "Total profit: " << profit << " dollars" << endl;
}
int main() {
// Define the supplier and retailers
Location supplier = {"Supplier", 40.7128, -74.0060, 0};
Location retailer1 = {"Retailer 2", 40.6975, -74.2599, 1000};
Location retailer2 = {"Retailer 1", 40.7505, -74.0034, 1500};
Location retailer3 = {"Retailer 3", 40.7392, -73.7813, 800};
// Store the locations in a vector
vector<Location> locations = {supplier, retailer1, retailer2, retailer3};

// Find the optimal route and print the results
double totalDistance;
vector<double> retailerDistances;
vector<int> optimalRoute = findOptimalRoute({retailer1, retailer2, retailer3}, supplier, totalDistance, retailerDistances);
printOptimalRoute({retailer1, retailer2, retailer3}, supplier, totalDistance, optimalRoute, retailerDistances);

return 0;
}