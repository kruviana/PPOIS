/**
 * @file PostMachine.h
 * @brief Заголовочный файл эмулятора Машины Поста.
 * @details Содержит объявления классов для управления бесконечной лентой, 
 * набором инструкций и общим состоянием абстрактной машины.
 * 
 * @author Круповская Диана
 * @see Tape
 * @see PostProgram
 * @see PostMachine
 */

#ifndef POST_MACHINE_H
#define POST_MACHINE_H

#include <string>
#include <iostream>
#include <map>
#include <vector>

/**
 * @class Tape
 * @brief Класс, реализующий бесконечную динамическую ленту Машины Поста.
 * @details Использует структуру данных std::map для эмуляции бесконечной памяти 
 * в обе стороны (положительные и отрицательные индексы) без выделения лишней памяти под пустые ячейки.
 */
class Tape {
private:
    std::map<int, bool> cells; ///< Хранилище ячеек ленты (индекс ячейки -> состояние метки 0/1)

public:
    /**
     * @brief Конструктор по умолчанию. Создает пустую ленту.
     */
    Tape();

    /**
     * @brief Деструктор. Освобождает ресурсы.
     */
    ~Tape();

    /**
     * @brief Проверить наличие метки в ячейке по указанному индексу.
     * @param index Целочисленный индекс ячейки на ленте.
     * @return true, если в ячейке стоит метка (1); false, если ячейка пуста (0).
     */
    bool getMark(int index) const;

    /**
     * @brief Установить или стереть метку в ячейке.
     * @param index Целочисленный индекс ячейки.
     * @param value Новое значение (true — поставить метку, false — стереть).
     */
    void setMark(int index, bool value);

    /**
     * @brief Полностью очистить ленту (стереть все метки).
     */
    void clear();

    /**
     * @brief Оператор проверки равенства двух лент.
     * @param other Другая лента для сравнения.
     * @return true, если состояние всех помеченных ячеек совпадает.
     */
    bool operator==(const Tape& other) const;

    /**
     * @brief Оператор проверки неравенства двух лент.
     * @param other Другая лента для сравнения.
     * @return true, если ленты различаются.
     */
    bool operator!=(const Tape& other) const;
};

/**
 * @struct Instruction
 * @brief Структура, представляющая одну команду (правило) программы Машины Поста.
 */
struct Instruction {
    char action;       ///< Символ действия: 'L' (влево), 'R' (вправо), 'V' (метка), 'X' (стирание), '?' (условие), 'H' (стоп)
    int next_line1;    ///< Номер следующей команды (или переход по ветке '1' для команды '?')
    int next_line2;    ///< Номер перехода по ветке '0' (используется исключительно для команды '?')
};

/**
 * @class PostProgram
 * @brief Класс, хранящий и управляющий набором правил (программой) для Машины Поста.
 */
class PostProgram {
private:
    std::map<int, Instruction> commands; ///< Набор пронумерованных инструкций программы

public:
    /**
     * @brief Конструктор по умолчанию для создания пустой программы.
     */
    PostProgram();
    
    /**
     * @brief Добавить новую команду в программу.
     * @param line_num Номер строки (команды).
     * @param action Символ действия.
     * @param next1 Номер следующей строки.
     * @param next2 Номер альтернативной строки (только для '?').
     */
    void addInstruction(int line_num, char action, int next1, int next2 = -1);

    /**
     * @brief Удалить команду из программы по номеру строки.
     * @param line_num Номер удаляемой строки.
     */
    void removeInstruction(int line_num);

    /**
     * @brief Проверить, существует ли команда с данным номером строки.
     * @param line_num Номер строки для проверки.
     * @return true, если команда найдена.
     */
    bool hasInstruction(int line_num) const;

    /**
     * @brief Получить константную ссылку на инструкцию по номеру строки.
     * @param line_num Номер искомой строки.
     * @return Константная ссылка на структуру Instruction.
     * @throws std::runtime_error Если команда отсутствует.
     */
    const Instruction& getInstruction(int line_num) const;

    /**
     * @brief Полностью очистить программу (удалить все правила).
     */
    void clear();

    /**
     * @brief Получить общее количество команд в программе.
     * @return Количество зарегистрированных правил.
     */
    size_t size() const;
};

/**
 * @class PostMachine
 * @brief Главный класс управляющего устройства абстрактной Машины Поста.
 * @details Инкапсулирует в себе ленту, программу, каретку и текущий указатель строки.
 * Обеспечивает выполнение алгоритма в пошаговом или автоматическом режимах.
 */
class PostMachine {
private:
    Tape tape;             ///< Объект динамической ленты
    PostProgram program;   ///< Объект набора инструкций (программы)
    int carriage;          ///< Текущий индекс ячейки, на которой стоит каретка
    int current_line;      ///< Номер текущей выполняемой строки программы
    bool is_halted;        ///< Флаг остановки (выполнялась ли команда 'H' или произошла ошибка)

public:
    /**
     * @brief Конструктор. Инициализирует начальное состояние машины (каретка на 0, строка 1).
     */
    PostMachine();

    /**
     * @brief Деструктор.
     */
    ~PostMachine();

    /**
     * @brief Загрузить программу (набор правил) из входного потока.
     * @param in Поток ввода (например, файл или std::cin).
     * @return true, если парсинг прошел успешно; false при ошибке формата.
     */
    bool loadProgram(std::istream& in);

    /**
     * @brief Загрузить начальное состояние ленты и положение каретки из потока.
     * @param in Поток ввода данных.
     * @return true при успешном чтении.
     */
    bool loadTapeState(std::istream& in);

    /**
     * @brief Принудительно установить каретку на определенную позицию.
     * @param position Индекс ячейки.
     */
    void setCarriage(int position);

    /**
     * @brief Получить текущую позицию каретки.
     * @return Индекс ячейки типа int.
     */
    int getCarriagePosition() const;

    /**
     * @brief Получить константную ссылку на объект ленты.
     * @return Объект Tape.
     */
    const Tape& getTape() const;

    /**
     * @brief Получить константную ссылку на текущую программу.
     * @return Объект PostProgram.
     */
    const PostProgram& getProgram() const;

    /**
     * @brief Получить номер текущей исполняемой строки.
     * @return Номер строки.
     */
    int getCurrentLine() const;

    /**
     * @brief Проверить, остановлена ли машина.
     * @return true, если симуляция завершена.
     */
    bool isHalted() const;

    /**
     * @brief Оператор префиксного инкремента (++machine).
     * @details Осуществляет ровно ОДИН шаг интерпретации алгоритма Поста.
     * Меняет состояние ленты, каретки и переводит указатель на следующую строку.
     * @return Ссылка на измененный объект Машины Поста (*this).
     */
    PostMachine& operator++();

    /**
     * @brief Запустить автоматическое выполнение всей программы до встречи команды 'H'.
     */
    void run();

    /**
     * @brief Оператор проверки эквивалентности состояний двух машин.
     * @param other Вторая машина для сравнения.
     * @return true, если все параметры (лента, каретка, строка) совпадают.
     */
    bool operator==(const PostMachine& other) const;

    /**
     * @brief Оператор проверки неэквивалентности состояний двух машин.
     * @param other Вторая машина для сравнения.
     * @return true, если конфигурации отличаются.
     */
    bool operator!=(const PostMachine& other) const;

    /**
     * @brief Дружественный оператор потокового вывода состояния машины.
     * @details Используется для реализации флага логирования (-log). 
     * Выводит текущую строку, позицию каретки и графический срез ленты.
     * @param os Поток вывода.
     * @param pm Константная ссылка на эмулируемую машину.
     * @return Ссылка на поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const PostMachine& pm);
};

#endif // POST_MACHINE_H
