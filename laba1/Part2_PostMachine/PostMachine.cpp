/**
 * @file PostMachine.cpp
 * @brief Реализация методов классов эмулятора Машины Поста.
 * @details Описывает логику выполнения пошагового симулятора, парсинг конфигурационных файлов и вывод данных.
 */

#include "PostMachine.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

// === РЕАЛИЗАЦИЯ КЛАССА TAPE ===
Tape::Tape() {}
Tape::~Tape() {}

bool Tape::getMark(int index) const {
    auto it = cells.find(index);
    if (it != cells.end()) {
        return it->second;
    }
    return false;
}

void Tape::setMark(int index, bool value) {
    if (value == false) {
        cells.erase(index); 
    } else {
        cells[index] = true;
    }
}

void Tape::clear() {
    cells.clear();
}

bool Tape::operator==(const Tape& other) const {
    return this->cells == other.cells;
}

bool Tape::operator!=(const Tape& other) const {
    return !(*this == other);
}

// === РЕАЛИЗАЦИЯ КЛАССА POSTPROGRAM ===
PostProgram::PostProgram() {}

void PostProgram::addInstruction(int line_num, char action, int next1, int next2) {
    Instruction inst;
    inst.action = action;
    inst.next_line1 = next1;
    inst.next_line2 = next2;
    commands[line_num] = inst;
}

void PostProgram::removeInstruction(int line_num) {
    commands.erase(line_num);
}

bool PostProgram::hasInstruction(int line_num) const {
    return commands.find(line_num) != commands.end();
}

const Instruction& PostProgram::getInstruction(int line_num) const {
    auto it = commands.find(line_num);
    if (it == commands.end()) {
        throw std::runtime_error("Команда не найдена!");
    }
    return it->second;
}

void PostProgram::clear() {
    commands.clear();
}

size_t PostProgram::size() const {
    return commands.size();
}

// === РЕАЛИЗАЦИЯ ГЛАВНОГО КЛАССА POSTMACHINE ===
PostMachine::PostMachine() : carriage(0), current_line(1), is_halted(false) {}
PostMachine::~PostMachine() {}

void PostMachine::setCarriage(int position) {
    carriage = position;
}

int PostMachine::getCarriagePosition() const {
    return carriage;
}

const Tape& PostMachine::getTape() const {
    return tape;
}

const PostProgram& PostMachine::getProgram() const {
    return program;
}

int PostMachine::getCurrentLine() const {
    return current_line;
}

bool PostMachine::isHalted() const {
    return is_halted;
}

/**
 * @brief Разбор строк программы Машины Поста.
 * Формат строки: [Номер] [Действие] [Переход1] ([Переход2] для '?')
 */
bool PostMachine::loadProgram(std::istream& in) {
    program.clear();
    int line_num, next1, next2;
    char action;
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::stringstream ss(line);
        if (ss >> line_num >> action >> next1) {
            if (action == '?') {
                if (ss >> next2) {
                    program.addInstruction(line_num, action, next1, next2);
                } else {
                    return false; // Ошибка: условный переход требует два адреса назначения
                }
            } else {
                program.addInstruction(line_num, action, next1);
            }
        }
    }
    return true;
}

bool PostMachine::loadTapeState(std::istream& in) {
    tape.clear();
    int start_pos;
    if (!(in >> start_pos)) return false;
    carriage = start_pos;

    int marked_idx;
    while (in >> marked_idx) {
        tape.setMark(marked_idx, true);
    }
    return true;
}

/**
 * @brief Выполнение одной микрокоманды.
 * @details Реализует систему команд Поста: R/L — движение, V/X — запись/стирание, ? — проверка ячейки, H — останов.
 */
PostMachine& PostMachine::operator++() {
    if (is_halted) return *this;

    // Если следующая строка отсутствует, завершаем симуляцию из-за ошибки в алгоритме
    if (!program.hasInstruction(current_line)) {
        is_halted = true;
        return *this;
    }

    const Instruction& inst = program.getInstruction(current_line);

    switch (inst.action) {
        case 'R':
            carriage++;
            current_line = inst.next_line1;
            break;
        case 'L':
            carriage--;
            current_line = inst.next_line1;
            break;
        case 'V':
            tape.setMark(carriage, true);
            current_line = inst.next_line1;
            break;
        case 'X':
            tape.setMark(carriage, false);
            current_line = inst.next_line1;
            break;
        case '?':
            if (tape.getMark(carriage) == true) {
                current_line = inst.next_line1;
            } else {
                current_line = inst.next_line2;
            }
            break;
        case 'H':
        default:
            is_halted = true;
            break;
    }
    return *this;
}

void PostMachine::run() {
    while (!is_halted) {
        ++(*this);
    }
}

bool PostMachine::operator==(const PostMachine& other) const {
    return this->carriage == other.carriage &&
           this->current_line == other.current_line &&
           this->is_halted == other.is_halted &&
           this->tape == other.tape;
}

bool PostMachine::operator!=(const PostMachine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PostMachine& pm) {
    os << "Команда: " << pm.current_line;
    if (pm.is_halted) os << " [СТОП]";
    os << " | Каретка на: " << pm.carriage << "\nЛента: ";

    // Отрисовываем фиксированное окно видимости вокруг каретки (радиус 5 ячеек)
    for (int i = pm.carriage - 5; i <= pm.carriage + 5; ++i) {
        if (i == pm.carriage) {
            os << "[" << (pm.tape.getMark(i) ? "1" : "0") << "] ";
        } else {
            os << (pm.tape.getMark(i) ? "1" : "0") << " ";
        }
    }
    os << "\n--------------------------------------------";
    return os;
}
