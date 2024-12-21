#ifndef ELEMENTS
#define ELEMENTS


#include "element.hpp"  // Для работы с классом Element


class ElementContainer {
private:
    Element** elements; // Массив указателей на элементы
    size_t capacity;    // Максимальная вместимость контейнера
    size_t size;        // Текущее количество элементов

    // Увеличение размера контейнера
    void resize();

public:
    // Конструктор и деструктор
    ElementContainer(size_t initialCapacity = 10);
    ~ElementContainer();

    // Методы управления коллекцией
    void removeElement(size_t index);
    void editElement(size_t index, const Element& updatedElement);
    void findElementByMass(const int& mass) const;

    // Методы сохранения/загрузки
    void writeToJSON(const std::string& filename) const;
    void readFromJSON(const std::string& filename);

    // Отображение элементов
    void displayElements() const;
    void displayMetals() const;

    // Геттеры
    int getSize() { return size; }

    // Операторы
    void operator+=(const Element& element);
};

#endif
