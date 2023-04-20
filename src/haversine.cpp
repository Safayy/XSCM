#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "location.hpp"
using namespace std;

// Calculating distance using Haversine formula
double calcDistance(Location loc1, Location loc2) {
  const double R = 6371;
  double lat1 = loc1.latitude * M_PI / 180.0;
  double lon1 = loc1.longitude * M_PI / 180.0;
  double lat2 = loc2.latitude * M_PI / 180.0;
  double lon2 = loc2.longitude * M_PI / 180.0;
  double dLat = lat2 - lat1;
  double dLon = lon2 - lon1;
  double a = sin(dLat / 2) * sin(dLat / 2) +
             cos(lat1) * cos(lat2) * sin(dLon / 2) * sin(dLon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double distance = R * c;
  return distance;
}