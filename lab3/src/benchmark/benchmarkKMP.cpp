#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <random>
#include <windows.h>

// Функция для генерации случайной строки заданной длины
std::string generateRandomString(int length) {
    static const std::string alphabet = "abcdefgh";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphabet[dis(gen)];
    }
    return result;
}

// Функция для вычисления префикс-функции
std::vector<int> prefixFunction(const std::string& pattern) {
    int n = pattern.length();
    std::vector<int> prefixes(n, 0);
    int j = 0;

    for (int i = 1; i < n; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefixes[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        prefixes[i] = j;
    }

    return prefixes;
}

// Функция для поиска всех вхождений pattern в text
std::vector<int> kmp(const std::string& pattern, const std::string& text) {
    int patternLen = pattern.length();
    int textLen = text.length();
    std::vector<int> prefixes = prefixFunction(pattern);
    std::vector<int> result;
    int j = 0;

    for (int i = 0; i < textLen; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = prefixes[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == patternLen) {
            result.push_back(i - j + 1);
            j = prefixes[j - 1];
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
    std::ofstream outputFile("kmp_performance.csv");
    outputFile << "TextSize,PatternSize,Time(seconds)\n";

    for (int textSize : textSizes) {
        for (int patternSize : patternSizes) {
            // Генерация случайного текста и паттерна
            std::string text = generateRandomString(textSize);
            std::string pattern = generateRandomString(patternSize);

            // Замер времени начала выполнения
            auto start = std::chrono::high_resolution_clock::now();

            // Выполнение алгоритма KMP
            std::vector<int> result = kmp(pattern, text);

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
    std::cout << "Результаты сохранены в файл kmp_performance.csv\n";

    return 0;
}