#include <cstdint>
#include <string>

struct PhoneRecord
{
    uint64_t number;
    char name[100];

    PhoneRecord(uint64_t phone, const std::string &n)
        : number(phone)
    {
        strncpy(name, n.c_str(), sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }
};
