#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "location.hpp"

using namespace std;



enum class Options {
  ADD_RETAILER,
  SHOW_OPTIMIZED_ROUTE,
  SHOW_UNOPTIMIZED_ROUTE,
  EXIT
};

// Print the optimal route in a nice fashion
void printOptimalRoute(vector<Location> retailers, Location supplier,
                       double totalDistance, vector<int> optimalRoute,
                       vector<double> retailerDistances) {
  cout << "Optimal route:" << endl;
  cout << supplier.name << " -> ";
  for (int i = 0; i < optimalRoute.size() - 1; i++) {
    cout << retailers[optimalRoute[i]].name << " -> ";
  }
  cout << supplier.name << endl;
  cout << "Total distance traveled: " << totalDistance << " km" << endl;
  double costOfGoods = 0;
  for (int i = 0; i < optimalRoute.size(); i++) {
    costOfGoods += retailers[optimalRoute[i]].costOfGoods;
  }

  double gasCost = totalDistance * 0.1;
  double wageCost = totalDistance * 11;
  double profit = costOfGoods - gasCost - wageCost;
  cout << "Total cost of goods: " << costOfGoods << " dollars" << endl;
  cout << "Total gas cost: " << gasCost << " dollars" << endl;
  cout << "Total wage cost: " << wageCost << " dollars" << endl;
  cout << "Total profit: " << profit << " dollars" << endl;
}