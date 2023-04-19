#include <string>

class Addressable {
public:
  Addressable(const std::string& name, const std::string& address)
    : name_(name), address_(address) {}

  // Getters for name and address
  const std::string& getName() const { return name_; }
  const std::string& getAddress() const { return address_; }

private:
  std::string name_;
  std::string address_;
};
