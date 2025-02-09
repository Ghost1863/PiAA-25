#include "desk.hpp"
#include "backtracking.hpp"
#include <iostream>
#include <ctime>
#include <limits>

int main() {
    int n;
    bool inputSuccess = false;
    while (!inputSuccess) {
        if (std::cin >> n) {
            if (n < 2 || n > 20)
                std::cout << "Size must be in range [2;20], try again\n";
            else
                inputSuccess = true;
        } else {
            std::cout << "Invalid input, please enter a number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    Desk desk(n);
    auto start = clock();
    if (n % 2 == 0) {
        desk.makeAnswerForEvenSize();
    }
    else if (!isPrime(n)) {
        auto factors = getFactors(n);
        int smallerFactor = factors.first;
        Desk smallDesk(smallerFactor);
        Desk smallAnswer = backtracking(smallDesk);
        desk = scaleSolution(smallAnswer, factors.second);
    } else {
        Desk answer = backtracking(desk);
        desk = answer;
    }

    std::cout << "Time to complete: " << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
    std::cout << desk.getSquareCount() << std::endl;
    for (auto elem : desk.getSquareList()) {
        std::cout << elem;
    }
    return 0;
}