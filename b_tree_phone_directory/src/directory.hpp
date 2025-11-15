#include "phone_record.hpp"
#include <vector>

class Directory
{
public:
    void addRecord(PhoneRecord reord);
    void editRecord(PhoneRecord record);
    void deleteRecord(std::string number);
    PhoneRecord *searchRecord(std::string number);

    void setDataSource(std::string path);
    void setIndexFile(std::string path);

    std::vector<PhoneRecord*> getAllRecords();

private:
    std::string dataFilename;
    std::string indexFilename;
};
