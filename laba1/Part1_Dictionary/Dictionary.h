#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <iostream>
#include <utility>

/**
 * @class Dictionary
 * @brief Класс, реализующий англо-русский словарь на основе бинарного дерева поиска.
 * @details В узлах дерева хранятся пары слов (английское и русское). 
 * Ключом для поиска и построения дерева является английское слово.
 * Класс обеспечивает независимость от пользовательского интерфейса.
 * 
 * @author Круповская Диана
 * @see Node
 */
class Dictionary {
private:
    /**
     * @struct Node
     * @brief Структура, представляющая узел бинарного дерева.
     */
    struct Node {
        std::string english; ///< Английское слово (ключ дерева)
        std::string russian; ///< Русский перевод слова
        Node* left;          ///< Указатель на левое поддерево
        Node* right;         ///< Указатель на правое поддерево

        /**
         * @brief Конструктор узла дерева.
         * @param eng Английское слово.
         * @param rus Русский перевод.
         */
        Node(const std::string& eng, const std::string& rus)
            : english(eng), russian(rus), left(nullptr), right(nullptr) {}
    };

    Node* root;          ///< Указатель на корень бинарного дерева
    size_t word_count;   ///< Текущее количество уникальных слов в словаре

    // Приватные рекурсивные методы для работы с деревом
    Node* insert(Node* node, const std::string& eng, const std::string& rus);
    Node* remove(Node* node, const std::string& eng, bool& success);
    Node* findMin(Node* node) const;
    Node* find(Node* node, const std::string& eng) const;
    void clear(Node* node);
    void copyTree(Node*& thisNode, const Node* otherNode);
    void printInOrder(std::ostream& os, Node* node) const;
    bool isEqual(const Node* n1, const Node* n2) const;

public:
    /**
     * @brief Конструктор по умолчанию.
     * @details Создает пустой словарь с нулевым количеством слов.
     */
    Dictionary();

    /**
     * @brief Деструктор класса.
     * @details Автоматически освобождает всю динамическую память, занятую узлами дерева.
     */
    ~Dictionary();

    /**
     * @brief Конструктор копирования (глубокое копирование).
     * @param other Ссылка на копируемый объект словаря.
     */
    Dictionary(const Dictionary& other);

    /**
     * @brief Оператор присваивания (глубокое копирование).
     * @param other Ссылка на правый операнд словаря.
     * @return Ссылка на текущий объект (*this) для цепочечных присваиваний.
     */
    Dictionary& operator=(const Dictionary& other);

    /**
     * @brief Оператор добавления/обновления слова (std::string).
     * @param pair Пара строк (английское слово, русский перевод).
     * @return Ссылка на измененный объект словаря (*this).
     */
    Dictionary& operator+=(const std::pair<std::string, std::string>& pair);
    
    /**
     * @brief Оператор добавления/обновления слова (C-style строки char*).
     * @param pair Пара указателей на C-строки (английское слово, русский перевод).
     * @return Ссылка на измененный объект словаря (*this).
     */
    Dictionary& operator+=(const std::pair<const char*, const char*>& pair);
    
    /**
     * @brief Оператор удаления слова из словаря.
     * @param eng Английское слово, которое необходимо удалить.
     * @return Ссылка на измененный объект словаря (*this).
     */
    Dictionary& operator-=(const std::string& eng);

    /**
     * @brief Оператор доступа по ключу для чтения и записи.
     * @details Если слово отсутствует в словаре, оно автоматически добавляется с пустым переводом.
     * @param eng Английское слово (ключ).
     * @return Ссылка на строку с русским переводом.
     */
    std::string& operator[](const std::string& eng);

    /**
     * @brief Оператор доступа по ключу для константных объектов (только чтение).
     * @param eng Английское слово (ключ).
     * @return Константная ссылка на строку с русским переводом.
     * @throws std::runtime_error Если слово не найдено в словаре.
     */
    const std::string& operator[](const std::string& eng) const;

    /**
     * @brief Получить текущее количество слов в словаре.
     * @return Количество записей типа size_t.
     */
    size_t size() const;

    /**
     * @brief Загрузить базу данных словаря из текстового файла.
     * @param filename Путь к файлу конфигурации.
     * @return true, если файл успешно прочитан; false в противном случае.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Оператор проверки на равенство двух словарей.
     * @details Сравнивает структуру дерева и содержимое каждого узла.
     * @param other Словарь для сравнения.
     * @return true, если словари полностью идентичны; иначе false.
     */
    bool operator==(const Dictionary& other) const;

    /**
     * @brief Оператор проверки на неравенство двух словарей.
     * @param other Словарь для сравнения.
     * @return true, если словари различаются; иначе false.
     */
    bool operator!=(const Dictionary& other) const;

    /**
     * @brief Дружественный оператор вывода словаря в поток.
     * @details Выводит все слова в алфавитном порядке (In-Order обход дерева).
     * @param os Поток вывода (например, std::cout).
     * @param dict Объект словаря для вывода.
     * @return Ссылка на поток вывода.
     */
    friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
};

#endif 
