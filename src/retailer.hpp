// #pragma once

// #include <iostream>
// #include <vector>
// #include <string>
// #include <ctime>
// #include <fstream>
// #include <json.hpp>

// using json = nlohmann::json;

// struct Order {
//     int order_id;
//     int product_id;
//     time_t date_ordered;
// };

// class Retailer {
// public:
//     std::string name;
//     std::string address;
//     std::vector<Order> orders;
//     int next_order_id;

//     Retailer(std::string name, std::string address);

//     bool addOrder(int product_id);

//     std::vector<Order> getOrders();
// };