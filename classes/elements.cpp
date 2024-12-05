#include "elements.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../libraries/json.hpp"

using namespace std;

ElementContainer::ElementContainer(int initialCapacity)
    : capacity(initialCapacity), size(0) {
    elements = new Element*[capacity];
}

ElementContainer::~ElementContainer() {
    for (int i = 0; i < size; ++i) {
        delete elements[i];
    }
    delete[] elements;
}

void ElementContainer::resize() {
    int newCapacity = capacity * 2;
    Element** newElements = new Element*[newCapacity];
    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

void ElementContainer::addElement(const Element& element) {
    if (size >= capacity) {
        resize();
    }
    elements[size++] = new Element(element);
}

void ElementContainer::removeElement(int index) {
    if (index >= size) {
        cout << "Выход за пределы индекса" << endl;
        return;
    }
    delete elements[index];
    for (int i = index; i < size - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    --size;
}

void ElementContainer::editElement(int index, const Element& updatedElement) {
    if (index >= size) {
        cout << "Выход за пределы индекса" << endl;
        return;
    }
    *elements[index] = updatedElement;
}

void ElementContainer::findElementByMass(const int& mass) const {
    for (int i = 0; i < size; ++i) {
        if (elements[i]->getMass() == mass) {
            elements[i]->shortDisplay();
        }
    }
}

void ElementContainer::writeToJSON(const string& filename) const {
    json jsonFile;
    jsonFile["count"] = size;

    for (int i = 0; i < size; ++i) {
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

    int newSize = jsonFile["count"];
    for (int i = 0; i < size; ++i) {
        delete elements[i];
    }
    delete[] elements;

    size = 0;
    capacity = newSize > 10 ? newSize : 10;
    elements = new Element*[capacity];

    for (const auto& elementData : jsonFile["elements"]) {
        Element* element = new Element(elementData);
        addElement(*element);
        delete element; // Temporary instance freed after addition
    }
}

void ElementContainer::displayElements() const {
    for (int i = 0; i < size; ++i) {
        elements[i]->display();
    }
}

void ElementContainer::displayMetals() const {
    for (int i = 0; i < size; ++i) {
        if (elements[i]->isType("metal")) {
           elements[i]-> shortDisplay();
        }
    }
}
