#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "nearest_neighbour.hpp"
#include "location.hpp"
#include "utils.hpp"

using namespace std;

std::string addToRouteFile(const std::string& str) {
    std::ifstream inFile("./data/route.txt");
    std::string content((std::istreambuf_iterator<char>(inFile)),
                         std::istreambuf_iterator<char>());
    inFile.close();

    std::ofstream outFile("./data/route.txt");
    if (outFile.is_open()) {
        outFile << str << std::endl;
        outFile << content;
        outFile.close();
        return "String successfully added to file";
    } else {
        return "Unable to open file!";
    }
}



// Main method
int main() {
  // Create some starting data
  cout << "******************************** XSCM ********************************* " << endl;
  Location supplier = {"Supplier", 40.7128, -74.0060, 0};
  Location retailer1 = {"Retailer 1", 40.6975, -74.2599, rand() % 1000 + 1};
  Location retailer2 = {"Retailer 2", 40.7392, -73.7813, rand() % 1000 + 1};
  Location retailer3 = {"Retailer 3", 40.7505, -74.0034, rand() % 1000 + 1};
  Location retailer4 = {"Retailer 4", 40.7504, -74.0033, rand() % 1000 + 1};
  vector<Location> locations = {retailer1, retailer2, retailer3, retailer4};

  double totalDistance;
  vector<double> retailerDistances;
  vector<int> optimalRoute = findOptimalRoute({retailer1, retailer2, retailer3}, supplier,
                       totalDistance, retailerDistances);

  string input;
  Options option;

  //Start while loop for user selection
  while (true) {
    cout << "Enter an option (add retailer, show optimized route, show unoptimized route, exit): "; //Show user options
    getline(cin, input);

    if (input == "add retailer") {
      option = Options::ADD_RETAILER;

    } else if (input == "show optimized route") {
      option = Options::SHOW_OPTIMIZED_ROUTE;
    } else if (input == "show unoptimized route") {
      option = Options::SHOW_UNOPTIMIZED_ROUTE;
    } else if (input == "exit") {
      option = Options::EXIT;
    } else {
      cout << "Invalid input. Please try again." << endl;
      continue;
    }

    switch (option) {

    case Options::SHOW_OPTIMIZED_ROUTE:
    {
      cout << "Optimized route:\n" << endl;
      optimalRoute = findOptimalRoute(locations, supplier,
                       totalDistance, retailerDistances);
      printOptimalRoute(locations, supplier, totalDistance, optimalRoute,
                        retailerDistances);
      std::string result = "Optimal route:\n" + supplier.name + " -> ";
      for (int i = 0; i < optimalRoute.size() - 1; i++) {
          result += locations[optimalRoute[i]].name + " -> ";
      }
      result += supplier.name + "\n";
      addToRouteFile(result);

      }
      break;
    

    case Options::SHOW_UNOPTIMIZED_ROUTE:
      {
        std::string routeString = "Unoptimized route:\n";
        routeString += supplier.name + " -> ";
        for (const Location& location : locations) {
            routeString += location.name + " -> ";
        }
        routeString += supplier.name + "\n";

        std::string results = addToRouteFile(routeString);
        std::cout << results << std::endl;

        std::cout << routeString << std::endl;
      }
      break;

    case Options::EXIT:
      cout << "Exiting program..." << endl;
      return 0;
      break;

    case Options::ADD_RETAILER:
      {
        string name1 = "";
        cout << "Enter the name of the new retailer: ";
        getline(cin, name1);
        cout << "Enter the latitude of the new retailer: ";
        double lat;
        cin >> lat;
        cout << "Enter the longitude of the new retailer: ";
        double lon;
        cin >> lon;
        cout << "Enter the cost of goods at the new retailer: ";
        double cost;
        cin >> cost;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        locations.push_back({name1, lat, lon, cost});
        cout << "Retailer added successfully." << endl;
      }
      break;

    default:
      cout << "Invalid option." << endl;
      break;
  }

}
  return 0;

}