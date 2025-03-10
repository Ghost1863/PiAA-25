#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <windows.h>

// Функция для генерации случайной строки заданной длины
std::string generateRandomString(int length) {
    static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphabet[dis(gen)];
    }
    return result;
}

// Наивный алгоритм поиска подстроки в строке
std::vector<int> naiveSearch(const std::string& pattern, const std::string& text) {
    std::vector<int> result;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            result.push_back(i); // Сохраняем индекс начала вхождения
        }
    }

    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Параметры для генерации данных
    std::vector<int> textSizes = {50000, 100000,200000,500000,1000000}; // Размеры текста
    std::vector<int> patternSizes = {1000}; // Размеры паттернов

    // Файл для сохранения результатов
    std::ofstream outputFile("naive_performance.csv");
    outputFile << "TextSize,PatternSize,Time(seconds)\n";

    for (int textSize : textSizes) {
        for (int patternSize : patternSizes) {
            // Генерация случайного текста и паттерна
            std::string text = generateRandomString(textSize);
            std::string pattern = generateRandomString(patternSize);

            // Замер времени начала выполнения
            auto start = std::chrono::high_resolution_clock::now();

            // Выполнение наивного алгоритма поиска
            std::vector<int> result = naiveSearch(pattern, text);

            // Замер времени окончания выполнения
            auto end = std::chrono::high_resolution_clock::now();

            // Вычисление времени выполнения
            std::chrono::duration<double> duration = end - start;

            // Сохранение результатов в файл
            outputFile << textSize << "," << patternSize << "," << duration.count() << "\n";

            // Вывод в консоль для отслеживания прогресса
            std::cout << "TextSize: " << textSize << ", PatternSize: " << patternSize
                      << ", Time: " << duration.count() << " seconds\n";
        }
    }

    outputFile.close();
    std::cout << "Результаты сохранены в файл naive_performance.csv\n";

    return 0;
}