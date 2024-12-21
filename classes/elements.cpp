#include "elements.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../libraries/json.hpp"

using namespace std;

ElementContainer::ElementContainer(size_t initialCapacity)
    : capacity(initialCapacity), size(0) {
    elements = new Element*[capacity];
}

ElementContainer::~ElementContainer() {
    for (size_t i = 0; i < size; ++i) {
        delete elements[i];
    }
    delete[] elements;
}

void ElementContainer::resize() {
    size_t newCapacity = capacity * 2;
    Element** newElements = new Element*[newCapacity];
    for (size_t i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

void ElementContainer::operator+=(const Element& element) {
    if (size >= capacity) {
        resize();
    }
    elements[size++] = new Element(element);
}

void ElementContainer::removeElement(size_t index) {
    if (index >= size) {
        cout << "Выход за пределы индекса" << endl;
        return;
    }
    delete elements[index];
    for (size_t i = index; i < size - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    --size;
}

void ElementContainer::editElement(size_t index, const Element& updatedElement) {
    if (index >= size) {
        cout << "Выход за пределы индекса" << endl;
        return;
    }
    *elements[index] = updatedElement;
}

void ElementContainer::findElementByMass(const int& mass) const {
    for (size_t i = 0; i < size; ++i) {
        if (elements[i]->getMass() == mass) {
            elements[i]->shortDisplay();
        }
    }
}

void ElementContainer::writeToJSON(const string& filename) const {
    json jsonFile;
    jsonFile["count"] = size;

    for (size_t i = 0; i < size; ++i) {
        jsonFile["elements"].push_back(elements[i]->getJSON());
    }

    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    outFile << jsonFile.dump(4); // Pretty print with 4-space indent
    outFile.close();
}

void ElementContainer::readFromJSON(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    json jsonFile;
    inFile >> jsonFile;

    size_t newSize = jsonFile["count"];
    for (size_t i = 0; i < size; ++i) {
        delete elements[i];
    }
    delete[] elements;

    size = 0;
    capacity = newSize > 10 ? newSize : 10;
    elements = new Element*[capacity];

    for (const auto& elementData : jsonFile["elements"]) {
        this->operator+=(Element(elementData));
    }
}

void ElementContainer::displayElements() const {
    cout << "Все элементы:" << endl;
    cout << string(80, '=') << endl; // Разделитель
    for (size_t i = 0; i < size; ++i) {
        cout << elements[i];
        cout << string(80, '=') << endl; // Разделитель
    }
}

void ElementContainer::displayMetals() const {
    cout << "Все элементы (металы):" << endl;
    cout << string(80, '=') << endl; // Разделитель
    for (size_t i = 0; i < size; ++i) {
        if (elements[i]->isType("metal")) {
           elements[i]-> shortDisplay();
        }
    }
}
