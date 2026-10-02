/**
 * @file Dictionary.cpp
 * @brief Реализация методов класса Dictionary.
 * @details Содержит алгоритмы вставки, удаления, поиска и обхода бинарного дерева поиска.
 */

#include "Dictionary.h"
#include <fstream>
#include <stdexcept>

Dictionary::Dictionary() : root(nullptr), word_count(0) {}

/**
 * @brief Рекурсивный метод очистки поддерева.
 * @param node Текущий узел для удаления.
 */
void Dictionary::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

Dictionary::~Dictionary() {
    clear(root);
}

/**
 * @brief Рекурсивное копирование структуры дерева.
 * @param thisNode Ссылка на узел текущего дерева, куда происходит копирование.
 * @param otherNode Указатель на узел исходного дерева.
 */
void Dictionary::copyTree(Node*& thisNode, const Node* otherNode) {
    if (otherNode == nullptr) {
        thisNode = nullptr;
    } else {
        thisNode = new Node(otherNode->english, otherNode->russian);
        copyTree(thisNode->left, otherNode->left);
        copyTree(thisNode->right, otherNode->right);
    }
}

Dictionary::Dictionary(const Dictionary& other) : root(nullptr), word_count(other.word_count) {
    copyTree(this->root, other.root);
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this != &other) {
        clear(root);
        word_count = other.word_count;
        copyTree(this->root, other.root);
    }
    return *this;
}

/**
 * @brief Рекурсивная вставка или обновление узла в дереве.
 * @param node Текущий узел поддерева.
 * @param eng Английское слово.
 * @param rus Русский перевод.
 * @return Указатель на измененный или новый узел.
 */
Dictionary::Node* Dictionary::insert(Node* node, const std::string& eng, const std::string& rus) {
    if (node == nullptr) {
        word_count++;
        return new Node(eng, rus);
    }
    if (eng < node->english) {
        node->left = insert(node->left, eng, rus);
    } else if (eng > node->english) {
        node->right = insert(node->right, eng, rus);
    } else {
        node->russian = rus; 
    }
    return node;
}

/**
 * @brief Рекурсивный поиск узла по английскому ключу.
 * @param node Текущий проверяемый узел поддерева.
 * @param eng Искомое английское слово.
 * @return Указатель на найденный узел, либо nullptr.
 */
Dictionary::Node* Dictionary::find(Node* node, const std::string& eng) const {
    if (node == nullptr || node->english == eng) {
        return node;
    }
    if (eng < node->english) {
        return find(node->left, eng);
    }
    return find(node->right, eng);
}

/**
 * @brief Поиск узла с минимальным ключом (самый левый узел).
 * @param node Корень поддерева для поиска.
 * @return Указатель на узел с минимальным значением ключа.
 */
Dictionary::Node* Dictionary::findMin(Node* node) const {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/**
 * @brief Рекурсивное удаление узла из дерева.
 * @details Реализует три сценария удаления узла: лист, узел с одним потомком, узел с двумя потомками.
 * @param node Текущий узел поддерева.
 * @param eng Ключ удаляемого слова.
 * @param success Флаг успешности выполнения удаления.
 * @return Указатель на обновленное поддерево.
 */
Dictionary::Node* Dictionary::remove(Node* node, const std::string& eng, bool& success) {
    if (node == nullptr) return nullptr;

    if (eng < node->english) {
        node->left = remove(node->left, eng, success);
    } else if (eng > node->english) {
        node->right = remove(node->right, eng, success);
    } else {
        success = true;
        // Случай 1 и 2: Нет потомков или только один потомок
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            word_count--;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            word_count--;
            return temp;
        }
        // Случай 3: У узла два потомка
        Node* temp = findMin(node->right);
        node->english = temp->english;
        node->russian = temp->russian;
        node->right = remove(node->right, temp->english, success);
    }
    return node;
}

Dictionary& Dictionary::operator+=(const std::pair<std::string, std::string>& pair) {
    root = insert(root, pair.first, pair.second);
    return *this;
}

Dictionary& Dictionary::operator+=(const std::pair<const char*, const char*>& pair) {
    root = insert(root, std::string(pair.first), std::string(pair.second));
    return *this;
}

Dictionary& Dictionary::operator-=(const std::string& eng) {
    bool success = false;
    root = remove(root, eng, success);
    return *this;
}

std::string& Dictionary::operator[](const std::string& eng) {
    Node* result = find(root, eng);
    if (result == nullptr) {
        root = insert(root, eng, "");
        result = find(root, eng);
    }
    return result->russian;
}

const std::string& Dictionary::operator[](const std::string& eng) const {
    Node* result = find(root, eng);
    if (result == nullptr) {
        throw std::runtime_error("Слово не найдено в словаре!");
    }
    return result->russian;
}

size_t Dictionary::size() const {
    return word_count;
}

/**
 * @brief Загрузить базу данных словаря из текстового файла.
 * Поддерживает форматы: "английское:русский перевод" и "английское русский".
 */
bool Dictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    size_t loaded_count = 0; 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::string eng = "";
        std::string rus = "";
        
        size_t delimiter_pos = line.find(':');
        
        if (delimiter_pos != std::string::npos) {
            eng = line.substr(0, delimiter_pos);
            rus = line.substr(delimiter_pos + 1);
        } else {
            size_t space_pos = line.find(' ');
            if (space_pos != std::string::npos) {
                eng = line.substr(0, space_pos);
                rus = line.substr(space_pos + 1);
            }
        }
        
        if (!eng.empty() && !rus.empty()) {
           
            while (!eng.empty() && (eng.back() == ' ' || eng.back() == '\r')) eng.pop_back();
            while (!eng.empty() && eng.front() == ' ') eng.erase(0, 1);
            while (!rus.empty() && (rus.back() == ' ' || rus.back() == '\r')) rus.pop_back();
            while (!rus.empty() && rus.front() == ' ') rus.erase(0, 1);
            
            if (!eng.empty() && !rus.empty()) {
                *this += std::make_pair(eng, rus);
                loaded_count++;
            }
        }
    }
    file.close();
    
    return loaded_count > 0; 
}


/**
 * @brief Симметричный обход дерева (In-Order) для вывода элементов по алфавиту.
 * @param os Поток вывода.
 * @param node Текущий обрабатываемый узел.
 */
void Dictionary::printInOrder(std::ostream& os, Node* node) const {
    if (node != nullptr) {
        printInOrder(os, node->left);
        os << node->english << " - " << node->russian << "\n";
        printInOrder(os, node->right);
    }
}

std::ostream& operator<<(std::ostream& os, const Dictionary& dict) {
    dict.printInOrder(os, dict.root);
    return os;
}

/**
 * @brief Рекурсивное поэлементное сравнение двух деревьев на идентичность.
 * @param n1 Узел первого дерева.
 * @param n2 Узел второго дерева.
 * @return true, если структуры и значения совпадают; иначе false.
 */
bool Dictionary::isEqual(const Node* n1, const Node* n2) const {
    if (!n1 && !n2) return true;
    if (!n1 || !n2) return false;
    return (n1->english == n2->english && n1->russian == n2->russian) &&
           isEqual(n1->left, n2->left) && isEqual(n1->right, n2->right);
}

bool Dictionary::operator==(const Dictionary& other) const {
    return isEqual(this->root, other.root);
}

bool Dictionary::operator!=(const Dictionary& other) const {
    return !(*this == other);
}
