/**
 * @file tests.cpp
 * @brief Модульные тесты для класса Dictionary с использованием UnitTest++.
 */

#include "unittest++/UnitTest++.h" 
#include "Dictionary.h"
#include <stdexcept>

SUITE(DictionaryTests)
{
    TEST(EmptyDictionarySize) {
        Dictionary dict;
        CHECK_EQUAL(0, dict.size());
    }

    TEST(SizeAfterAddingOneWord) {
        Dictionary dict;
        dict += std::make_pair("apple", "яблоко");
        CHECK_EQUAL(1, dict.size());
    }

    TEST(SizeAfterAddingMultipleWords) {
        Dictionary dict;
        dict += std::make_pair("apple", "яблоко");
        dict += std::make_pair("banana", "банан");
        dict += std::make_pair("cat", "кот");
        CHECK_EQUAL(3, dict.size());
    }

    TEST(SizeAfterUpdatingWord) {
        Dictionary dict;
        dict += std::make_pair("apple", "яблоко");
        dict += std::make_pair("apple", "новое_яблоко");
        CHECK_EQUAL(1, dict.size());
    }

    TEST(SizeAfterDeletion) {
        Dictionary dict;
        dict += std::make_pair("apple", "яблоко");
        dict -= "apple";
        CHECK_EQUAL(0, dict.size());
    }

    TEST(FindExistingWordString) {
        Dictionary dict;
        dict += std::make_pair(std::string("dog"), std::string("собака"));
        CHECK_EQUAL("собака", dict["dog"]);
    }

        TEST(FindExistingWordCStyle) {
        Dictionary dict;
        // Явно создаем пару из const char* для проверки перегрузки
        std::pair<const char*, const char*> c_pair = {"dog", "собака"};
        dict += c_pair;
        CHECK_EQUAL("собака", dict["dog"]);
    }


    TEST(UpdateTranslation) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict["cat"] = "кошка";
        CHECK_EQUAL("кошка", dict["cat"]);
    }

    TEST(BracketOperatorCreatesNewWord) {
        Dictionary dict;
        std::string translation = dict["unknown"];
        CHECK_EQUAL("", translation);
        CHECK_EQUAL(1, dict.size());
    }

    TEST(ConstBracketOperatorThrowsException) {
        Dictionary dict;
        const Dictionary& constDict = dict;
        CHECK_THROW(constDict["missing"], std::runtime_error);
    }

    TEST(OrderOfInsertionLeftBranch) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict += std::make_pair("apple", "яблоко");
        CHECK_EQUAL("яблоко", dict["apple"]);
    }

    TEST(OrderOfInsertionRightBranch) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict += std::make_pair("dog", "собака");
        CHECK_EQUAL("собака", dict["dog"]);
    }

    TEST(DeleteLeafNode) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict += std::make_pair("apple", "яблоко");
        dict -= "apple";
        CHECK_EQUAL(1, dict.size());
    }

    TEST(DeleteNodeWithOneChild) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict += std::make_pair("apple", "яблоко");
        dict += std::make_pair("ant", "муравей");
        dict -= "apple";
        CHECK_EQUAL("муравей", dict["ant"]);
    }

    TEST(DeleteNodeWithTwoChildren) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict += std::make_pair("apple", "яблоко");
        dict += std::make_pair("dog", "собака");
        dict -= "cat";
        CHECK_EQUAL(2, dict.size());
        CHECK_EQUAL("собака", dict["dog"]);
    }

    TEST(DeleteNonExistentWord) {
        Dictionary dict;
        dict += std::make_pair("cat", "кот");
        dict -= "fox";
        CHECK_EQUAL(1, dict.size());
    }

    TEST(ClearTreeViaDestructionBehavior) {
        Dictionary* dict = new Dictionary();
        dict->operator+=(std::make_pair("a", "б"));
        delete dict;
        CHECK(true);
    }

    TEST(DeleteAllWordsOneByOne) {
        Dictionary dict;
        dict += std::make_pair("a", "1");
        dict += std::make_pair("b", "2");
        dict -= "a";
        dict -= "b";
        CHECK_EQUAL(0, dict.size());
    }

    TEST(DeleteRootAndLeaveEmpty) {
        Dictionary dict;
        dict += std::make_pair("root", "корень");
        dict -= "root";
        CHECK_EQUAL(0, dict.size());
    }
    TEST(ConstructorCopying) {
        Dictionary original;
        original += std::make_pair("book", "книга");
        Dictionary copy(original);
        CHECK_EQUAL("книга", copy["book"]);
        CHECK_EQUAL(original.size(), copy.size());
    }

    TEST(CopyIndependence) {
        Dictionary original;
        original += std::make_pair("book", "книга");
        Dictionary copy(original);
        copy += std::make_pair("pen", "ручка");
        CHECK_EQUAL(1, original.size());
        CHECK_EQUAL(2, copy.size());
    }

    TEST(AssignmentOperator) {
        Dictionary dict1;
        dict1 += std::make_pair("home", "дом");
        Dictionary dict2;
        dict2 = dict1;
        CHECK_EQUAL("дом", dict2["home"]);
    }

    TEST(SelfAssignment) {
        Dictionary dict;
        dict += std::make_pair("home", "дом");
        dict = dict;
        CHECK_EQUAL(1, dict.size());
    }

    TEST(DeepCopyTreeStructure) {
        Dictionary dict1;
        dict1 += std::make_pair("m", "1");
        dict1 += std::make_pair("a", "2");
        Dictionary dict2 = dict1;
        CHECK_EQUAL("2", dict2["a"]);
    }

    TEST(AssignToExistingDictionary) {
        Dictionary dict1;
        dict1 += std::make_pair("1", "один");
        Dictionary dict2;
        dict2 += std::make_pair("2", "два");
        dict2 = dict1;
        CHECK_EQUAL(1, dict2.size());
    }

    TEST(OperatorEqualForIdenticalDictionaries) {
        Dictionary d1, d2;
        d1 += std::make_pair("apple", "яблоко");
        d2 += std::make_pair("apple", "яблоко");
        CHECK(d1 == d2);
    }

    TEST(OperatorNotEqualForDifferentDictionaries) {
        Dictionary d1, d2;
        d1 += std::make_pair("apple", "яблоко");
        d2 += std::make_pair("banana", "банан");
        CHECK(d1 != d2);
    }

    TEST(OperatorEqualForEmptyDictionaries) {
        Dictionary d1, d2;
        CHECK(d1 == d2);
    }

    TEST(LoadFromFileFailureReturnsFalse) {
        Dictionary dict;
        CHECK(!dict.loadFromFile("non_existent_file_123.txt"));
    }

    TEST(ComplexChainOfActions) {
        Dictionary dict;
        dict += std::make_pair("a", "1");
        dict += std::make_pair("b", "2");
        dict["a"] = "99";
        dict -= "b";
        CHECK_EQUAL("99", dict["a"]);
        CHECK_EQUAL(1, dict.size());
    }
}

int main() {
    return UnitTest::RunAllTests();
}
