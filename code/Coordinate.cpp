#include "Coordinate.h"
#include <iostream>
#include <math.h>
#include <sstream>  // Voor stringstream
#include <string>


Coordinate::Coordinate()
{
    this->x = 0;
    this->y = 0;
}

Coordinate::Coordinate(int x, int y)
{
    this->x = x;
    this->y = y;
}


int Coordinate::distance_2(const Coordinate & other) const
{
    return (int) (pow(this->x - other.x,2) + pow(this->y - other.y,2));
}

std::string Coordinate::toString() const
{
    std::stringstream ss;
    ss << "(" << this->x << "," << this->y << ")";
    return ss.str();
}

const Coordinate Coordinate::operator+(const Coordinate &other) const
{
    return Coordinate(this->x + other.x,this->y + other.y);
}

const Coordinate Coordinate::operator-(const Coordinate & other) const
{
    return Coordinate(this->x - other.x,this->y - other.y);
}

const Coordinate Coordinate::operator*(const float scaler) const
{
    return Coordinate(scaler * this->x,scaler * this->y);
}

Coordinate &Coordinate::operator=(const Coordinate & other)
{
    this->x = other.x;
    this->y = other.y;
    return *this;
}

bool Coordinate::operator==(const Coordinate & other) const
{
    return (this->x == other.x && this->y == other.y);
}

const Coordinate Coordinate::operator-() const
{
    return Coordinate(-this->x,-this->y);
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
