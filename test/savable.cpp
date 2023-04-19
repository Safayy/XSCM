// class Savable {
// public:
//     virtual ~Savable() {}
//     virtual void saveToFile(const std::string& filename) {
//         json jsonData = toJson();
//         std::ofstream file(filename);
//         if (file.is_open()) {
//             file << jsonData.dump(2);
//             file.close();
//         }
//     }
//     virtual void loadFromFile(const std::string& filename) {
//         std::ifstream file(filename);
//         if (file.is_open()) {
//             std::string fileContents((std::istreambuf_iterator<char>(file)),
//                                      std::istreambuf_iterator<char>());
//             file.close();
//             json jsonData = json::parse(fileContents);
//             fromJson(jsonData);
//         }
//     }
//     virtual json toJson() = 0;
//     virtual void fromJson(const json& jsonData) = 0;
// };