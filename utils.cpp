#include "utils.hpp"

// Функция для поиска элемента по атомной массе
void findElementByMass(Element*& elements, int size) {
    int mass;
    cout << "Введите массу: ";
    while (!(cin >> mass) || mass < 0) {
        cout << "Неверная масса элемента. Повторите: ";
        cin.clear();
    }

    for (int i = 0; i < size; ++i) {
        if (elements[i].getMass() == mass) {
            cout << "Найден элемент: " << endl;
            elements[i].shortDisplay();

            cout << endl;
        }
    }
    cout << "Элемент с атомной массой " << mass << " не найден." << endl;
}

// Функция для вывода всех металлов
void displayMetals(Element*& elements, int size) {
    cout << "Металлы в массиве:" << endl;

    bool found = false; // Флаг для проверки наличия металлов
    for (int i = 0; i < size; ++i) {
        if (elements[i].isType("metal")) {
            elements[i].shortDisplay();
            found = true; // Если найден металл, устанавливаем флаг
        }
    }
    cout << endl;
    if (!found) {
        cout << "Металлы не найдены в массиве." << endl;
    }
}