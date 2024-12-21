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
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    outFile << *this ;
}

void ElementContainer::readFromJSON(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    inFile >> *this;
}

void ElementContainer::displayElements() const {
    cout << "Все элементы:" << endl;
    cout << string(80, '=') << endl; // Разделитель
    for (size_t i = 0; i < size; ++i) {
        cout << *elements[i];
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

ofstream& operator<<(ofstream& out, const ElementContainer& cont) {
    json jsonFile;
    jsonFile["count"] = cont.size;

    for (size_t i = 0; i < cont.size; ++i) {
        jsonFile["elements"].push_back(cont.elements[i]->getJSON());
    }

    out << jsonFile.dump(4); // Pretty print with 4-space indent

    return out;
}

ifstream& operator>>(ifstream& in, ElementContainer& cont) {
    json jsonFile;
    in >> jsonFile;

    size_t newSize = jsonFile["count"];
    for (size_t i = 0; i < cont.size; ++i) {
        delete cont.elements[i];
    }
    delete[] cont.elements;

    cont.size = 0;
    cont.capacity = newSize > 10 ? newSize : 10;
    cont.elements = new Element*[cont.capacity];

    for (const auto& elementData : jsonFile["elements"]) {
        cont += (Element(elementData));
    }

    return in;
}
