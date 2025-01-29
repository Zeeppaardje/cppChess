#include "Coordinate.h"


#ifndef HASHFUNCTIONS
#define HASHFUNCTIONS

struct HashFunction {
    size_t operator()(const Coordinate& coord) const {
        std::string str = coord.toString();
        return std::hash<std::string>()(str);
    }
};


#endif

