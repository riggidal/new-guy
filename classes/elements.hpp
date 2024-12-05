#ifndef ELEMENTS
#define ELEMENTS


#include "element.hpp"  // Для работы с классом Element


class ElementContainer {
private:
    Element** elements; // Массив указателей на элементы
    int capacity;    // Максимальная вместимость контейнера
    int size;        // Текущее количество элементов

    // Увеличение размера контейнера
    void resize();

public:
    // Конструктор и деструктор
    ElementContainer(int initialCapacity = 10);
    ~ElementContainer();

    // Методы управления коллекцией
    void addElement(const Element& element);
    void removeElement(int index);
    void editElement(int index, const Element& updatedElement);
    void findElementByMass(const int& mass) const;

    // Методы сохранения/загрузки
    void writeToJSON(const std::string& filename) const;
    void readFromJSON(const std::string& filename);

    // Отображение элементов
    void displayElements() const;
    void displayMetals() const;

    // Геттеры
    int getSize() { return size; }
};

#endif
