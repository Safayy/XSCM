#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "haversine.hpp"
#include "location.hpp"

using namespace std;

vector<int> findOptimalRoute(vector<Location> retailers, Location supplier, double& totalDistance, vector<double>& retailerDistances);

#endif
