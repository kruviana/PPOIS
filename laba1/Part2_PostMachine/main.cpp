/**
 * @file main.cpp
 * @brief Точка входа для эмулятора Машины Поста с поддержкой логгирования.
 * @author Ваше Имя
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "PostMachine.h"

int main(int argc, char* argv[]) {
    // Устанавливаем корректную локализацию для Mac/Консоли
    std::setlocale(LC_ALL, "Russian");

    // 1. Проверяем, передан ли хотя бы один аргумент (путь к файлу)
    if (argc < 2) {
        std::cout << "Ошибка! Не указан путь к файлу конфигурации.\n";
        std::cout << "Использование: ./post_machine <путь_к_файлу> [-log]\n";
        return 1;
    }

    std::string config_path = argv[1];
    bool enable_log = false;

    // 2. Проверяем наличие флага -log в аргументах командной строки
    if (argc > 2 && std::string(argv[2]) == "-log") {
        enable_log = true;
    }

    // Открываем файл конфигурации
    std::ifstream file(config_path);
    if (!file.is_open()) {
        std::cout << "Ошибка! Не удалось открыть файл: " << config_path << "\n";
        return 1;
    }

    PostMachine machine;

    // 3. Последовательное чтение комбинированного файла конфигурации
    // Первая строка файла — состояние ленты. Остальные строки — программа Поста.
    std::string tape_line;
    if (std::getline(file, tape_line)) {
        std::stringstream tape_stream(tape_line);
        if (!machine.loadTapeState(tape_stream)) {
            std::cout << "Ошибка! Неверный формат начального состояния ленты в первой строке.\n";
            return 1;
        }
    } else {
        std::cout << "Ошибка! Файл конфигурации пуст.\n";
        return 1;
    }

    // Передаем остаток файла в метод загрузки программы
    if (!machine.loadProgram(file)) {
        std::cout << "Ошибка! Не удалось корректно прочитать программу Машины Поста.\n";
        return 1;
    }
    file.close();

    std::cout << "[ИНФО] Файл успешно загружен. Начинаем интерпретацию...\n\n";

    // 4. Логика выполнения в зависимости от наличия флага -log
    if (enable_log) {
        // Пошаговый режим: выводим состояние ДО начала и после каждого выполнения
        std::cout << "=== НАЧАЛЬНОЕ СОСТОЯНИЕ ===\n" << machine << "\n";
        
        while (!machine.isHalted()) {
            // Осуществляем ровно ОДИН шаг при помощи оператора преинкремента ++
            ++machine; 
            // Выводим текущее состояние ленты и каретки на консоль
            std::cout << machine << "\n";
        }
    } else {
        // Обычный режим: выполняем всё и сразу без спама в консоль
        machine.run();
        std::cout << "=== ФИНАЛЬНОЕ СОСТОЯНИЕ ===\n" << machine << "\n";
    }

    std::cout << "\n[УСПЕХ] Программа Машины Поста завершила работу.\n";
    return 0;
}
