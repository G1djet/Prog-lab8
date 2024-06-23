#include <iostream>
#include <vector>

/**
 * @struct Node
 * @brief Узел односвязного списка.
 *
 * @param data Данные узла.
 * @param next Указатель на следующий узел.
 */
struct Node {
    int data;
    Node* next;

    /**
     * @brief Конструктор узла.
     * @param value Значение данных узла.
     */
    Node(int value) : data(value), next(nullptr) {}
};

/**
 * @class LinkedList
 * @brief Класс для работы с односвязным списком.
 *
 * @param head Указатель на первый узел списка.
 */
class LinkedList {
private:
    Node* head;

public:
    /**
     * @brief Конструктор класса LinkedList.
     * Создает пустой односвязный список.
     */
    LinkedList() : head(nullptr) {}

    /**
     * @brief Деструктор класса LinkedList.
     * Освобождает память, занятую узлами списка.
     */
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    /**
     * @brief Добавляет новый элемент в конец списка.
     * @param value Значение данных нового узла.
     */
    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    /**
     * @brief Удаляет элементы из связанного списка, присутствующие во втором списке.
     * @param other Ссылка на другой связанный список.
     */
    void removeElementsInOtherList(LinkedList& other) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            bool shouldDelete = false;
            Node* otherCurrent = other.head;
            while (otherCurrent != nullptr) {
                if (current->data == otherCurrent->data) {
                    shouldDelete = true;
                    break;
                }
                otherCurrent = otherCurrent->next;
            }

            if (shouldDelete) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    /**
     * @brief Выводит список на консоль.
     */
    void printList() {
        Node* current = head;
        std::cout << "List: ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

/**
 * @brief Точка входа программы.
 *
 * Создает два связанных списка, заполняет их значениями, введенными пользователем,
 * и удаляет из первого списка элементы, присутствующие во втором списке.
 * Выводит оба списка на консоль.
 *
 * @return Возвращает 0 в случае успешного завершения.
 */
int main() {
    LinkedList list1, list2;

    std::cout << "Enter elements for the first list (enter 0 to stop):" << std::endl;
    int num;
    while (true) {
        std::cin >> num;
        if (num == 0) {
            break;
        }
        list1.append(num);
    }

    std::cout << "Enter elements for the second list (enter 0 to stop):" << std::endl;
    while (true) {
        std::cin >> num;
        if (num == 0) {
            break;
        }
         list2.append(num);
    }

    list1.printList();
    list2.printList();

    list1.removeElementsInOtherList(list2);

    std::cout << "The list after removing elements present in the second list:" << std::endl;
    list1.printList();

    return 0;
}