/**
 * @file tests.cpp
 * @brief Модульные тесты для Машины Поста с использованием UnitTest++.
 */

#include "unittest++/UnitTest++.h"
#include "PostMachine.h"
#include <sstream>

SUITE(PostMachineTests)
{
    // --- ТЕСТЫ ЛЕНТЫ (TAPE) (1-6) ---
    TEST(TapeDefaultEmpty) {
        Tape tape;
        CHECK_EQUAL(false, tape.getMark(0));
        CHECK_EQUAL(false, tape.getMark(-100));
    }

    TEST(TapeSetAndGetMark) {
        Tape tape;
        tape.setMark(5, true);
        tape.setMark(-5, true);
        CHECK_EQUAL(true, tape.getMark(5));
        CHECK_EQUAL(true, tape.getMark(-5));
    }

    TEST(TapeEraseMark) {
        Tape tape;
        tape.setMark(10, true);
        tape.setMark(10, false); // Стираем
        CHECK_EQUAL(false, tape.getMark(10));
    }

    TEST(TapeClearMethod) {
        Tape tape;
        tape.setMark(1, true);
        tape.setMark(2, true);
        tape.clear();
        CHECK_EQUAL(false, tape.getMark(1));
        CHECK_EQUAL(false, tape.getMark(2));
    }

    TEST(TapeEqualityOperator) {
        Tape t1, t2;
        t1.setMark(3, true);
        t2.setMark(3, true);
        CHECK(t1 == t2);
    }

    TEST(TapeInequalityOperator) {
        Tape t1, t2;
        t1.setMark(3, true);
        t2.setMark(4, true);
        CHECK(t1 != t2);
    }

    // --- ТЕСТЫ ПРОГРАММЫ (POSTPROGRAM) (7-11) ---
    TEST(ProgramAddAndCheck) {
        PostProgram prog;
        prog.addInstruction(1, 'R', 2);
        CHECK(prog.hasInstruction(1));
        CHECK_EQUAL(1, prog.size());
    }

    TEST(ProgramGetInstructionData) {
        PostProgram prog;
        prog.addInstruction(1, 'L', 2);
        const Instruction& inst = prog.getInstruction(1);
        CHECK_EQUAL('L', inst.action);
        CHECK_EQUAL(2, inst.next_line1);
    }

    TEST(ProgramBranchInstructionData) {
        PostProgram prog;
        prog.addInstruction(2, '?', 3, 4);
        const Instruction& inst = prog.getInstruction(2);
        CHECK_EQUAL('?', inst.action);
        CHECK_EQUAL(3, inst.next_line1);
        CHECK_EQUAL(4, inst.next_line2);
    }

    TEST(ProgramRemoveInstruction) {
        PostProgram prog;
        prog.addInstruction(1, 'H', 0);
        prog.removeInstruction(1);
        CHECK(!prog.hasInstruction(1));
    }

    TEST(ProgramClearMethod) {
        PostProgram prog;
        prog.addInstruction(1, 'R', 2);
        prog.clear();
        CHECK_EQUAL(0, prog.size());
    }

    // --- ТЕСТЫ ИНИЦИАЛИЗАЦИИ МАШИНЫ (12-16) ---
    TEST(MachineDefaultState) {
        PostMachine pm;
        CHECK_EQUAL(0, pm.getCarriagePosition());
        CHECK_EQUAL(1, pm.getCurrentLine());
        CHECK_EQUAL(false, pm.isHalted());
    }

    TEST(MachineSetCarriage) {
        PostMachine pm;
        pm.setCarriage(42);
        CHECK_EQUAL(42, pm.getCarriagePosition());
    }

    TEST(MachineLoadTapeStateValid) {
        PostMachine pm;
        std::stringstream ss("5 1 2"); // Каретка на 5, метки на 1 и 2
        CHECK(pm.loadTapeState(ss));
        CHECK_EQUAL(5, pm.getCarriagePosition());
        CHECK_EQUAL(true, pm.getTape().getMark(1));
    }

    TEST(MachineLoadTapeStateInvalid) {
        PostMachine pm;
        std::stringstream ss(""); // Пустой поток
        CHECK(!pm.loadTapeState(ss));
    }

    TEST(MachineLoadProgramValid) {
        PostMachine pm;
        std::stringstream ss("1 R 2\n2 H 0");
        CHECK(pm.loadProgram(ss));
        CHECK_EQUAL(2, pm.getProgram().size());
    }

    // --- ТЕСТЫ ОПЕРАТОРА ШАГА ++ (ИНКРЕМЕНТ) (17-23) ---
    TEST(StepOperatorMoveRight) {
        PostMachine pm;
        std::stringstream ss("1 R 2");
        pm.loadProgram(ss);
        pm.setCarriage(0);
        
        ++pm; // Делаем шаг вправо
        CHECK_EQUAL(1, pm.getCarriagePosition());
        CHECK_EQUAL(2, pm.getCurrentLine());
    }

    TEST(StepOperatorMoveLeft) {
        PostMachine pm;
        std::stringstream ss("1 L 5");
        pm.loadProgram(ss);
        pm.setCarriage(0);
        
        ++pm; // Делаем шаг влево
        CHECK_EQUAL(-1, pm.getCarriagePosition());
        CHECK_EQUAL(5, pm.getCurrentLine());
    }

    TEST(StepOperatorSetMark) {
        PostMachine pm;
        std::stringstream ss("1 V 2");
        pm.loadProgram(ss);
        
        ++pm; // Ставим метку
        CHECK_EQUAL(true, pm.getTape().getMark(0));
    }

    TEST(StepOperatorEraseMark) {
        PostMachine pm;
        std::stringstream ss("0\n1 X 2"); // Начальное состояние ленты (каретка на 0) + программа
        std::stringstream tape_ss("0 0");  // Поставим метку на 0 ячейку
        pm.loadTapeState(tape_ss);
        std::stringstream prog_ss("1 X 2");
        pm.loadProgram(prog_ss);
        
        ++pm; // Стираем метку
        CHECK_EQUAL(false, pm.getTape().getMark(0));
    }

    TEST(StepOperatorBranchOnTrue) {
        PostMachine pm;
        std::stringstream tape_ss("0 0"); // Метка на 0
        pm.loadTapeState(tape_ss);
        std::stringstream prog_ss("1 ? 8 9");
        pm.loadProgram(prog_ss);
        
        ++pm; // Должен уйти на строку 8
        CHECK_EQUAL(8, pm.getCurrentLine());
    }

    TEST(StepOperatorBranchOnFalse) {
        PostMachine pm;
        std::stringstream tape_ss("0"); // Нет меток
        pm.loadTapeState(tape_ss);
        std::stringstream prog_ss("1 ? 8 9");
        pm.loadProgram(prog_ss);
        
        ++pm; // Должен уйти на строку 9
        CHECK_EQUAL(9, pm.getCurrentLine());
    }

    TEST(StepOperatorHaltCommand) {
        PostMachine pm;
        std::stringstream ss("1 H 0");
        pm.loadProgram(ss);
        
        ++pm;
        CHECK(pm.isHalted());
    }

    // --- ТЕСТЫ ЦИКЛА ВЫПОЛНЕНИЯ И СРАВНЕНИЯ (24-30) ---
    TEST(MachineRunFullProgram) {
        PostMachine pm;
        std::stringstream prog_ss("1 V 2\n2 R 3\n3 H 0");
        pm.loadProgram(prog_ss);
        
        pm.run(); // Запускаем всё до упора
        CHECK(pm.isHalted());
        CHECK_EQUAL(1, pm.getCarriagePosition());
        CHECK_EQUAL(true, pm.getTape().getMark(0));
    }

    TEST(StepOnHaltedMachineDoesNothing) {
        PostMachine pm;
        std::stringstream ss("1 H 0");
        pm.loadProgram(ss);
        ++pm; // Остановили
        int line = pm.getCurrentLine();
        ++pm; // Еще один шаг на остановленной машине
        CHECK_EQUAL(line, pm.getCurrentLine());
    }

    TEST(MachineEqualityIdentical) {
        PostMachine pm1, pm2;
        CHECK(pm1 == pm2);
    }

    TEST(MachineInequalityDifferentCarriage) {
        PostMachine pm1, pm2;
        pm2.setCarriage(1);
        CHECK(pm1 != pm2);
    }

    TEST(LoadProgramMissingBranchParameter) {
        PostMachine pm;
        std::stringstream ss("1 ? 2"); // Для '?' нужно два числа ветвления
        CHECK(!pm.loadProgram(ss));
    }

    TEST(StepOnMissingInstructionHalts) {
        PostMachine pm; // Программа пустая, строки 1 нет
        ++pm;
        CHECK(pm.isHalted());
    }

    TEST(ComplexTapeStateSimulation) {
        PostMachine pm;
        std::stringstream tape_ss("0 1 3 5");
        pm.loadTapeState(tape_ss);
        CHECK_EQUAL(true, pm.getTape().getMark(1));
        CHECK_EQUAL(false, pm.getTape().getMark(2));
        CHECK_EQUAL(true, pm.getTape().getMark(3));
    }
}

int main() {
    return UnitTest::RunAllTests();
}
