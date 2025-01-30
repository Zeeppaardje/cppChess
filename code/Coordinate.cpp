#include "Coordinate.hpp"
#include <iostream>
#include <math.h>
#include <sstream>  // Voor stringstream
#include <string>


Coordinate::Coordinate() : x(0), y(0) {}

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}


int Coordinate::distance_2(const Coordinate & other) const
{
    return (int) (pow(x - other.x,2) + pow(y - other.y,2));
}

std::string Coordinate::toString() const
{
    std::stringstream ss;
    ss << "(" << x << "," << y << ")";
    return ss.str();
}

const Coordinate Coordinate::operator+(const Coordinate &other) const
{
    return Coordinate(x + other.x,y + other.y);
}

const Coordinate Coordinate::operator-(const Coordinate & other) const
{
    return Coordinate(x - other.x,y - other.y);
}

const Coordinate Coordinate::operator*(const float scaler) const
{
    return Coordinate(scaler * x,scaler * y);
}

Coordinate &Coordinate::operator=(const Coordinate & other)
{
    x = other.x;
    y = other.y;
    return *this;
}

bool Coordinate::operator==(const Coordinate & other) const
{
    return (x == other.x && y == other.y);
}

const Coordinate Coordinate::operator-() const
{
    return Coordinate(-x,-y);
}

const Coordinate operator*(const float scaler, const Coordinate &coord)
{
    return coord * scaler;
}

std::ostream &operator<<(std::ostream &outputStream, const Coordinate &coord)
{
    outputStream << coord.toString() << std::endl;
    return outputStream;
}
