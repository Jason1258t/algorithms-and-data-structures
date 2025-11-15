#include <cstdint>

struct BTreeNode
{
    uint16_t m;
    uint16_t keysCount;
    uint64_t data[];

    BTreeNode(uint16_t m) : m{m} {
        keysCount = m - 1;
    }
};
