#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include "location.hpp"
#include "utils.hpp"

enum class Options {
  ADD_RETAILER,
  SHOW_OPTIMIZED_ROUTE,
  SHOW_UNOPTIMIZED_ROUTE,
  EXIT
};

void printOptimalRoute(std::vector<Location> retailers, Location supplier,
                       double totalDistance, std::vector<int> optimalRoute,
                       std::vector<double> retailerDistances);

#endif