#ifndef BACKTRACKING_HPP
#define BACKTRACKING_HPP

#include <queue>
#include <iostream>
#include "desk.hpp" 

bool isPrime(int n);
std::pair<int, int> getFactors(int n);
Desk backtracking(Desk desk);
Desk scaleSolution(const Desk& smallDesk, int scaleFactor);

#endif 