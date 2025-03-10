#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// Функция для вычисления префикс-функции
vector<int> prefixFunction(const string& pattern) {
    int n = pattern.length();
    vector<int> prefixes(n, 0);
    int j = 0;

    cout << "Вычисление префикс-функции для паттерна: " << pattern << endl;

    for (int i = 1; i < n; ++i) {
        cout << "\nИтерация " << i << ":" << endl;
        cout << "  Сравниваем символы: pattern[" << i << "] = " << pattern[i]
             << " и pattern[" << j << "] = " << pattern[j] << endl;

        while (j > 0 && pattern[i] != pattern[j]) {
            cout << "    Символы не совпали. Обновляем j с " << j << " на " << prefixes[j - 1] << endl;
            j = prefixes[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            cout << "    Символы совпали. Увеличиваем j с " << j << " на " << j + 1 << endl;
            ++j;
        }

        prefixes[i] = j;
        cout << "  Устанавливаем prefixes[" << i << "] = " << prefixes[i] << endl;

        // Выводим текущее состояние массива prefixes
        cout << "  Текущий массив prefixes: ";
        for (int k = 0; k <= i; ++k) {
            cout << prefixes[k] << " ";
        }
        cout << endl;
    }

    cout << "\nИтоговый массив префикс-функции: ";
    for (int val : prefixes) {
        cout << val << " ";
    }
    cout << endl;

    return prefixes;
}

// Функция для поиска циклического сдвига
int findCyclicShift(const string& pattern, const string& text) {
    int patternLen = pattern.length();
    int textLen = text.length();
    vector<int> prefixes = prefixFunction(pattern);
    int j = 0;

    cout << "\nПоиск циклического сдвига для паттерна: " << pattern << " в тексте: " << text << endl;

    for (int i = 0; i < 2 * textLen; ++i) {
        int idx = i % textLen;  // Используем индекс по модулю длины строки
        cout << "\nИтерация " << i << ":" << endl;
        cout << "  Индекс в тексте: " << idx << ", символ: " << text[idx] << endl;
        cout << "  Текущее значение j: " << j << endl;

        while (j > 0 && text[idx] != pattern[j]) {
            cout << "    Символы не совпали: text[" << idx << "] = " << text[idx]
                 << " != pattern[" << j << "] = " << pattern[j] << endl;
            cout << "    Обновляем j с " << j << " на " << prefixes[j - 1] << endl;
            j = prefixes[j - 1];
            cout << "    Новое значение j: " << j << endl;
        }

        if (text[idx] == pattern[j]) {
            cout << "    Символы совпали: text[" << idx << "] = " << text[idx]
                 << " == pattern[" << j << "] = " << pattern[j] << endl;
            ++j;
            cout << "    Увеличиваем j до " << j << endl;
        }

        if (j == patternLen) {
            cout << "    Найдено полное совпадение! Индекс начала сдвига: " << (i - j + 1) << endl;
            return i - j + 1;
        }
    }

    cout << "    Совпадение не найдено." << endl;
    return -1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string text, pattern;
    cout << "Введите текст: ";
    cin >> text;
    cout << "Введите паттерн: ";
    cin >> pattern;

    if (text.length() != pattern.length()) {
        cout << "Длины текста и паттерна не совпадают. Результат: -1" << endl;
    } else {
        int result = findCyclicShift(pattern, text);
        cout << "Результат: " << result << endl;
    }

    return 0;
}