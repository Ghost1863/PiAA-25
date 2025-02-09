#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>

struct Square {
    int size; // длина стороны квадрата
    int x;
    int y;

    Square(int size, int x, int y);
    friend std::ostream& operator<<(std::ostream& os, const Square& square);
};

#endif // SQUARE_HPP