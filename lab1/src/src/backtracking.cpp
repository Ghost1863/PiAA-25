#include "backtracking.hpp"

Desk backtracking(Desk desk) {
    if(isPrime(desk.getDeskSize())){
        desk.addSquaresForPrimeSizes();
    }
    std::queue<Desk> queue; // кладем исходный стол в очередь
    queue.push(desk);
    int currentIteration = 1, operationCounter = 0; // инициализация счетчиков для количества операций и итераций

    while (!queue.front().isFull()) {
        //std::cout << currentIteration << " " << "iteration\n";
        Desk s = queue.front(); // создаем копию первого стола из очереди для взаимодействия
        std::pair<int, int> emptyCell = s.emptyCell(); // находим свободную клетку на столе
        for (int i = desk.getDeskSize() - 1; i > 0; i--) {
         // пытаемся поставить квадрат на место пустой клетки, начинаем попытки от наибольшего возможного варианта
            if (s.canAdd(emptyCell.first, emptyCell.second, i)) { // проверка возможности поставить квадрат в стол
                Desk cur = s;
                cur.addSquare(i, emptyCell.first, emptyCell.second, cur.getSquareCount());
                //std::cout << "Current step\n" << cur << std::endl;
                if (cur.isFull()) { // в случае, если мы полностью заполнили стол, мы возвращаем полученный итог
                    std::cout << "operation count: " << operationCounter << std::endl;
                    return cur;
                }
                queue.push(cur); // если стол был заполнен не до конца, полученный этап решения кладем в конец очереди и идем дальше
            }
            operationCounter++;
        }
        queue.pop();// удаляем итерацию стола, над которой мы работали,
        // т.к. мы либо добавили в очередь все возможные дальнейшие расстановки на данном этапе, либо полностью его заполнили
        currentIteration++;
    }
    std::cout << "operation count: " << operationCounter << std::endl;
    return queue.front();
}

Desk scaleSolution(const Desk& smallDesk, int scaleFactor) {
    int newDeskSize = smallDesk.getDeskSize() * scaleFactor;
    Desk newDesk(newDeskSize);

    for (const auto& square : smallDesk.getSquareList()) {
        int newSize = square.size * scaleFactor;
        int newX = square.x * scaleFactor;
        int newY = square.y * scaleFactor;
        newDesk.addSquare(newSize, newX, newY, newDesk.getSquareCount());
    }

    return newDesk;
}

bool isPrime(int n) {
    if (n == 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

std::pair<int, int> getFactors(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return {i, n / i};
        }
    }
    return {1, n}; // Если число простое, возвращаем {1, n}
}