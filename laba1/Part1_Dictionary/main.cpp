/**
 * @mainpage Англо-Русский Словарь (Лабораторная работа №1)
 *
 * @section intro_sec Описание проекта
 * Данный проект реализует Англо-Русский словарь на базе структуры данных 
 * "Бинарное дерево поиска" (BST).
 *
 * @section features_sec Возможности программы:
 * - Добавление слов с помощью оператора += (std::string и char*)
 * - Удаление слов с помощью оператора -=
 * - Поиск и модификация перевода через оператор []
 * - Определение точного количества слов в словаре
 * - Автоматическая загрузка базы данных из текстового файла
 *
 * @section testing_sec Тестирование:
 * В проекте реализовано 30 автоматических юнит-тестов с помощью UnitTest++.
 */

/**
 * @file main.cpp
 * @brief Файл пользовательского интерфейса (консольное меню).
 * @author Круповская Диана
 */

#include <iostream>
#include "Dictionary.h"

void showMenu() {
    std::cout << "===== АНГЛО-РУССКИЙ СЛОВАРЬ =====\n";
    std::cout << "1. Показать все слова (по алфавиту)\n";
    std::cout << "2. Добавить или обновить слово (+=)\n";
    std::cout << "3. Удалить слово из словаря (-=)\n";
    std::cout << "4. Найти перевод слова ([])\n";
    std::cout << "5. Показать количество слов в словаре\n";
    std::cout << "6. Загрузить словарь из файла\n";
    std::cout << "0. Выйти из программы\n";
    std::cout << "=================================\n";
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Dictionary dict; 
    int choice = -1;

    while (choice != 0) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Ошибка! Введите цифру от 0 до 6.\n\n";
            continue;
        }

        std::string eng, rus;

        switch (choice) {
            case 1: 
                std::cout << "\n--- Содержимое словаря ---\n";
                if (dict.size() == 0) {
                    std::cout << "Словарь пока пуст.\n";
                } else {
                    std::cout << dict; 
                }
                std::cout << "--------------------------\n\n";
                break;

            case 2: 
                std::cout << "Введите английское слово: ";
                std::cin >> eng;
                std::cout << "Введите русский перевод: ";
                std::cin >> rus;
                
                dict += std::make_pair(eng, rus);
                std::cout << "Слово успешно добавлено/обновлено!\n\n";
                break;

            case 3: 
                std::cout << "Введите английское слово для удаления: ";
                std::cin >> eng;
                
                dict -= eng;
                std::cout << "Операция удаления выполнена.\n\n";
                break;

            case 4: 
                std::cout << "Введите английское слово для поиска: ";
                std::cin >> eng;
                try {
                    std::string translation = const_cast<const Dictionary&>(dict)[eng];
                    std::cout << "Перевод: " << translation << "\n\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n\n";
                }
                break;

            case 5: 
                std::cout << "Сейчас в словаре слов: " << dict.size() << "\n\n";
                break;

            case 6: 
                std::cout << "Введите имя файла (например, dict.txt): ";
                std::cin >> eng; 
                if (dict.loadFromFile(eng)) {
                    std::cout << "Словарь успешно загружен!\n\n";
                } else {
                    std::cout << "Не удалось открыть файл. Проверьте имя и путь.\n\n";
                }
                break;

            case 0:
                std::cout << "Завершение работы программы. До свидания!\n";
                break;

            default:
                std::cout << "Неверный пункт меню. Попробуйте еще раз.\n\n";
                break;
        }
    }

    return 0; 
}
