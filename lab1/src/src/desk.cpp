#include "desk.hpp"

Desk::Desk(int n) : deskSize(n), squareCounter(0) {
    this->map = std::vector<std::vector<int>>();
    for(auto i = 0; i < deskSize; i++){
        this->map.push_back(std::vector<int>(n));
    }
    this->squareList = std::vector<Square>();
    this->squareCounter = 0;
}

void Desk::addSquaresForPrimeSizes() {
    addSquare((deskSize + 1) / 2, 0, 0, squareCounter);
    addSquare((deskSize) / 2, 0, (deskSize + 1) / 2, squareCounter);
    addSquare((deskSize) / 2, (deskSize + 1) / 2, 0, squareCounter);
}

void Desk::makeAnswerForEvenSize() {
    addSquare(deskSize / 2, 0, 0, squareCounter);
    addSquare(deskSize / 2, deskSize / 2, 0, squareCounter);
    addSquare(deskSize / 2, 0, deskSize / 2, squareCounter);
    addSquare(deskSize / 2, deskSize / 2, deskSize / 2, squareCounter);
}

void Desk::addSquare(int size, int x, int y, int color) {
    Square square(size, x, y);
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            map[i][j] = color + 1;
        }
    }
    squareList.push_back(square);
    squareCounter++;
}

bool Desk::isFull() const {
    for (int i = 0; i < deskSize; i++) {
        for (int j = 0; j < deskSize; j++) {
            if (map[i][j] == 0) return false;
        }
    }
    return true;
}

bool Desk::canAdd(int x, int y, int size) const {
    if (y + size > deskSize || x + size > deskSize) return false;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            if (map[i][j] != 0) return false;
        }
    }
    return true;
}

std::pair<int, int> Desk::emptyCell() const {
    for (int i = 0; i < deskSize; i++) {
        for (int j = 0; j < deskSize; j++) {
            if (map[i][j] == 0) return {i, j};
        }
    }
    return {-1, -1};
}

int Desk::getDeskSize() const {
    return deskSize;
}

std::vector<Square> Desk::getSquareList() const {
    return squareList;
}

int Desk::getSquareCount() const {
    return squareCounter;
}

std::vector<std::vector<int>> Desk::getMap() const {
    return map;
}

std::ostream& operator<<(std::ostream& os, const Desk& desk) {
    for (const auto& elem : desk.getMap()) {
        for (const auto& cell : elem) {
            os << cell << " ";
        }
        os << '\n';
    }
    return os;
}
