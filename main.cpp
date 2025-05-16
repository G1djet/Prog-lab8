#include <iostream>
#include <vector>
#include <algorithm> // для sort, unique
#include <limits>  // Добавлено для numeric_limits


using namespace std;

/**
 * @struct Node
 * @brief Узел односвязного списка.
 *
 * @param data Целочисленное значение узла.
 * @param next Указатель на следующий узел в списке.
 */
struct Node {
    int data;
    Node* next;
    
    /**
     * @brief Конструктор узла.
     * @param val Значение, которое будет храниться в узле.
     */
    Node(int val) : data(val), next(nullptr) {}
};

/**
 * @class LinkedList
 * @brief Класс для работы с линейным односвязным списком.
 *
 * Поддерживает добавление элементов, удаление по позициям, вывод и другие операции.
 */
class LinkedList {
private:
    Node* head; ///< Указатель на начало списка
    
public:
    /**
     * @brief Конструктор по умолчанию. Создает пустой список.
     */
    LinkedList() : head(nullptr) {}
    
    /**
     * @brief Деструктор. Освобождает всю память, занятую списком.
     */
    ~LinkedList() {
        clear();
    }
    
    /**
     * @brief Добавляет новый элемент в конец списка.
     * @param val Значение для добавления.
     */
    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    /**
     * @brief Удаляет элемент на указанной позиции (нумерация с 1).
     * @param pos Позиция элемента для удаления.
     * @note Если позиция некорректна (меньше 1 или больше размера списка), 
     *       функция не выполняет никаких действий.
     */
    void removeAt(int pos) {
        if (pos < 1 || !head) {
            return;
        }
        
        if (pos == 1) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }
        
        Node* current = head;
        for (int i = 1; i < pos - 1 && current->next; ++i) {
            current = current->next;
        }
        
        if (current->next) {
            Node* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
    }
    
    /**
     * @brief Очищает список, удаляя все элементы.
     */
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    /**
     * @brief Выводит содержимое списка в консоль.
     */
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    /**
     * @brief Возвращает количество элементов в списке.
     * @return Текущий размер списка.
     */
    int size() const {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

/**
 * @brief Считывает последовательность целых чисел с консоли и создает список.
 * @return Заполненный список чисел.
 * @note Ввод завершается при вводе любого нечислового значения.
 */
LinkedList readList() {
    LinkedList list;
    cout << "Введите последовательность целых чисел (закончите ввод символом не цифры):\n";
    
    int num;
    while (cin >> num) {
        list.append(num);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return list;
}

/**
 * @brief Считывает с консоли позиции для удаления элементов.
 * @return Вектор с номерами позиций (начиная с 1).
 * @note Ввод завершается при вводе любого нечислового значения.
 */
vector<int> readPositions() {
    vector<int> positions;
    cout << "Введите позиции для удаления (закончите ввод символом не цифры):\n";
    
    int pos;
    while (cin >> pos) {
        if (pos > 0) {
            positions.push_back(pos);
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return positions;
}

/**
 * @brief Удаляет из списка элементы на указанных позициях.
 * @param list Список, из которого будут удаляться элементы.
 * @param positions Вектор позиций для удаления.
 * @note Позиции сортируются в обратном порядке для корректного удаления.
 *       Дубликаты позиций автоматически удаляются.
 */
void removeElementsAtPositions(LinkedList& list, const vector<int>& positions) {
    vector<int> sortedPositions = positions;
    sort(sortedPositions.rbegin(), sortedPositions.rend());
    sortedPositions.erase(unique(sortedPositions.begin(), sortedPositions.end()), sortedPositions.end());
    
    for (int pos : sortedPositions) {
        list.removeAt(pos);
    }
}

/**
 * @brief Главная функция программы.
 * 
 * 1. Создает список чисел на основе ввода пользователя.
 * 2. Запрашивает позиции для удаления.
 * 3. Удаляет указанные элементы.
 * 4. Выводит исходный и измененный списки.
 * 
 * @return 0 при успешном завершении.
 */
int main() {
    LinkedList list = readList();
    
    cout << "Исходный список: ";
    list.print();
    
    vector<int> positions = readPositions();
    removeElementsAtPositions(list, positions);
    
    cout << "Результат после удаления: ";
    list.print();
    
    return 0;
}
