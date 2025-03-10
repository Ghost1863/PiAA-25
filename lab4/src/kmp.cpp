#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#define RESET "\x1B[0m"
#define GREEN(text) "\x1B[32m" << text << RESET
#define RED(text) "\x1B[31m" << text << RESET
#define BLUE(text) "\x1B[34m" << text << RESET
#define YELLOW(text) "\x1B[33m" << text << RESET
#define MAGENTA(text) "\x1B[35m" << text << RESET
#define CYAN(text) "\x1B[36m" << text << RESET

// Функция для вычисления префикс-функции
std::vector<int> prefixFunction(const std::string& pattern) {
    int n = pattern.length();
    std::vector<int> prefixes(n, 0);
    int j = 0;

    std::cout << MAGENTA("Вычисление префикс-функции для паттерна: " << pattern )<< std::endl;

    for (int i = 1; i < n; ++i) {
        std::cout << GREEN("\nИтерация " << i << ":") << std::endl;
        std::cout << "  i = " << i << ", j = " << j << std::endl;
        std::cout << "  Сравниваем символы: pattern[" << i << "] = " << pattern[i]
                  << " и pattern[" << j << "] = " << pattern[j] << std::endl;

        while (j > 0 && pattern[i] != pattern[j]) {
            std::cout << "    Символы не совпали: pattern[" << i << "] = " << pattern[i]
                      << " != pattern[" << j << "] = " << pattern[j] << std::endl;
            std::cout << "    Обновляем j с " << j << " на " << prefixes[j - 1] << std::endl;
            j = prefixes[j - 1];
            std::cout << "    Новое значение j = " << j << std::endl;
        }

        if (pattern[i] == pattern[j]) {
            std::cout << "    Символы совпали: pattern[" << i << "] = " << pattern[i]
                      << " == pattern[" << j << "] = " << pattern[j] << std::endl;
            j++;
            std::cout << "    Увеличиваем j до " << j << std::endl;
        }

        prefixes[i] = j;
        std::cout << "  Устанавливаем prefixes[" << i << "] = " << prefixes[i] << std::endl;

        // Выводим текущее состояние массива prefixes
        std::cout << "  Текущий массив prefixes: ";
        for (int k = 0; k <= i; ++k) {
            std::cout << prefixes[k] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nИтоговый массив префикс-функции: ";
    for (int val : prefixes) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return prefixes;
}

// Функция для поиска всех вхождений pattern в text
std::vector<int> kmp(const std::string& pattern, const std::string& text) {
    int patternLen = pattern.length();
    int textLen = text.length();
    std::vector<int> prefixes = prefixFunction(pattern);
    std::vector<int> result;
    int j = 0;

    std::cout << MAGENTA("\nПоиск вхождений паттерна \"" << pattern << "\" в тексте \"" << text << "\":") << std::endl;

    for (int i = 0; i < textLen; ++i) {
        std::cout << GREEN("\nИтерация " << i << ":") << std::endl;
        std::cout << "  i = " << i << ", j = " << j << std::endl;
        std::cout << "  Сравниваем символы: text[" << i << "] = " << text[i]
                  << " и pattern[" << j << "] = " << pattern[j] << std::endl;

        while (j > 0 && text[i] != pattern[j]) {
            std::cout << "    Символы не совпали: text[" << i << "] = " << text[i]
                      << " != pattern[" << j << "] = " << pattern[j] << std::endl;
            std::cout << "    Обновляем j с " << j << " на " << prefixes[j - 1] << std::endl;
            j = prefixes[j - 1];
            std::cout << "    Новое значение j = " << j << std::endl;
        }

        if (text[i] == pattern[j]) {
            std::cout << "    Символы совпали: text[" << i << "] = " << text[i]
                      << " == pattern[" << j << "] = " << pattern[j] << std::endl;
            j++;
            std::cout << "    Увеличиваем j до " << j << std::endl;
        }

        if (j == patternLen) {
            std::cout << "    Найдено вхождение паттерна на позиции " << (i - j + 1) << std::endl;
            result.push_back(i - j + 1);  // Сохраняем индекс начала вхождения
            std::cout << "    Обновляем j с " << j << " на " << prefixes[j - 1] << std::endl;
            j = prefixes[j - 1];  // Восстанавливаем индекс паттерна
            std::cout << "    Новое значение j = " << j << std::endl;
        }

        // Выводим текущее состояние массива result
        std::cout << "  Текущий массив result: ";
        for (int val : result) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nИтоговый массив индексов вхождений: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return result;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::string pattern, text;
    std::cout << "Введите паттерн: ";
    std::cin >> pattern;
    std::cout << "Введите текст: ";
    std::cin >> text;

    std::vector<int> answer = kmp(pattern, text);

    if (answer.empty()) {
        std::cout << "Вхождений не найдено. Результат: -1" << std::endl;
    } else {
        std::cout << "Результат: ";
        for (size_t i = 0; i < answer.size(); ++i) {
            if (i > 0) {
                std::cout << ",";
            }
            std::cout << answer[i];
        }
        std::cout << std::endl;
    }

    return 0;
}