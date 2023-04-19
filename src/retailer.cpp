// #include <iostream>
// #include <vector>
// #include <string>
// #include <ctime>
// #include <fstream>
// #include <json.hpp>
// #include "retailer.hpp"

// Retailer::Retailer(std::string name, std::string address) {
//     this->name = name;
//     this->address = address;
//     next_order_id = 1;
// }

// bool Retailer::addOrder(int product_id) {
//     Order newOrder;
//     newOrder.order_id = next_order_id;
//     newOrder.product_id = product_id;
//     newOrder.date_ordered = time(0);

//     next_order_id++;

//     orders.push_back(newOrder);
//     return true;
// }

// std::vector<Order> Retailer::getOrders() {
//     return orders;
// }