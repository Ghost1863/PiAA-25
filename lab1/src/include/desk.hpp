#ifndef DESK_HPP
#define DESK_HPP

#include <vector>
#include <queue>
#include <iostream>
#include <cmath>
#include "square.hpp"

class Desk {
private:
    std::vector<std::vector<int>> map; // двумерный массив, отображающий расположение квадратов
    int deskSize;    // длина стороны стола
    int squareCounter; // количество квадратов
    std::vector<Square> squareList; // список характеристик квадратов, выводимый в конце

public:
    Desk(int n);
    void addSquaresForPrimeSizes();
    void makeAnswerForEvenSize();
    void addSquare(int size, int x, int y, int color);
    bool isFull() const;
    bool canAdd(int x, int y, int size) const;
    std::pair<int, int> emptyCell() const;
    int getDeskSize() const;
    std::vector<Square> getSquareList() const;
    int getSquareCount() const;
    std::vector<std::vector<int>> getMap() const;
    friend std::ostream& operator<<(std::ostream& os, const Desk& desk);
};

#endif // DESK_HPP