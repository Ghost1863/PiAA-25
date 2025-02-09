#include "square.hpp"

Square::Square(int size, int x, int y) : size(size), x(x), y(y) {}

std::ostream& operator<<(std::ostream& os, const Square& square) {
    os << square.x << ' ' << square.y << ' ' << square.size << std::endl;
    return os;
}