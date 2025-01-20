#include "utils.h"

std::string zfill(std::string n, int z)
{
    int l = z - std::min(z, (int)n.length());
    return std::string(l, '0') + n;
}

std::string zfill(int n, int z)
{
    return zfill(std::to_string(n), z);
}

std::string zfill(int n)
{
    return zfill(n, 3);
}