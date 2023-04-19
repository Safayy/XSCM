#include <string>
#include "addressable.cpp"

class Supplier : public Addressable {
public:
    Supplier(std::string name, std::string address, std::string contactPerson, std::string email)
        : Addressable(name, address), m_contactPerson(contactPerson), m_email(email) {}

    std::string getContactPerson() const { return m_contactPerson; }
    std::string getEmail() const { return m_email; }

private:
    std::string m_contactPerson;
    std::string m_email;
};