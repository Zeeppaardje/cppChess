/* Ik weet dat Vectors al bestaan maar dit is een oefening*/


#include <iostream>


#ifndef COORDINATE

#define COORDINATE




class Coordinate{
    // constructor / destructor

    public:
        Coordinate();
        Coordinate(int x,int y);
    public:
        int x;
        int y;

        // methods
        int distance_2(const Coordinate&) const;
        std::string toString() const;
        // methode overloading
        const Coordinate operator+(const Coordinate&) const;
        const Coordinate operator-(const Coordinate&) const;

        // maal
        const Coordinate operator*(const float) const;
        const friend Coordinate operator*(const float scaler,const Coordinate& coord);

        Coordinate& operator=(const Coordinate&);
        bool operator==(const Coordinate&) const;
        friend std::ostream& operator<<(std::ostream& outputStream, const Coordinate& coord);
        const Coordinate operator-() const;
    
};


#endif