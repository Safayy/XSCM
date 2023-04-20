#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "haversine.hpp"
#include "location.hpp"
using namespace std;

// Find optimal route using Nearest Neighbour Algorithm
vector<int> findOptimalRoute(vector<Location> retailers, Location supplier,
                             double &totalDistance,
                             vector<double> &retailerDistances) {
  int numRetailers = retailers.size();
  vector<bool> visited(numRetailers, false);
  vector<int> optimalRoute(numRetailers + 1);
  optimalRoute[0] = 0;
  visited[0] = true;

  for (int i = 1; i < numRetailers; i++) {
    double minDistance = INFINITY;
    int nearestNeighbor = -1;
    for (int j = 0; j < numRetailers; j++) {
      if (!visited[j]) {
        double distance =
            calcDistance(retailers[optimalRoute[i - 1]], retailers[j]);
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
  for (int i = 0; i < numRetailers - 1; i++) {
    distance += calcDistance(retailers[optimalRoute[i]],
                             retailers[optimalRoute[i + 1]]);
    retailerDistances.push_back(calcDistance(retailers[optimalRoute[i]],
                                             retailers[optimalRoute[i + 1]]));
  }
  distance += calcDistance(retailers[optimalRoute[numRetailers - 1]], supplier);
  totalDistance = distance;
  retailerDistances.push_back(
      calcDistance(retailers[optimalRoute[numRetailers - 1]], supplier));

  return optimalRoute;
}
