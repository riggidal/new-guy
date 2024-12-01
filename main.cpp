#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Для форматирования вывода

#include "element.hpp"

using namespace std;

void readFromConsole(Element *&elements, int &size) {

    // Очистим предыдущие значния
    delete[] elements;

    cout << "Введите количество элементов: " << endl;
    cin >> size;
    while (!(cin >> size) || size < 0) {
        cout << "Неверное количество элементов. Повторите: ";
        cin.clear();
    }

    for (int i = 0; i < size; i++)
    {
        Element newElement;
        newElement.readFromConsole();

        elements[i] = newElement;
    }
    
}

// Функция для поиска элемента по атомной массе
void findElementByMass(Element*& elements, int size, int mass) {
    for (int i = 0; i < size; ++i) {
        if (elements[i].getMass() == mass) {
            cout << "Найден элемент: " << endl;
            elements[i].shortDisplay();

            cout << endl;
        }
    }
    cout << "Элемент с атомной массой " << mass << " не найден." << endl;
}

// Функция для вывода всех элементов
void displayAllElements(Element*& elements, int size) {
    cout << "Все элементы:" << endl;
    cout << left << setw(20) << "Название" << setw(10) << "Символ" << setw(10) << "Номер" << setw(15) << "Тип" << setw(15) << "Атомная масса" << "Электронная конфигурация" << endl;
    for (int i = 0; i < size; ++i) {
        elements[i].display();
    }
}

// Функция для вывода всех металлов
void displayMetals(Element* elements, int size) {
    cout << "Металлы в массиве:" << endl;
    bool found = false; // Флаг для проверки наличия металлов
    for (int i = 0; i < size; ++i) {
        if (elements[i].isType("metal")) {
            elements[i].shortDisplay();
            found = true; // Если найден металл, устанавливаем флаг
        }
    }
    cout << "\n";
    if (!found) {
        cout << "Металлы не найдены в массиве." << endl;
    }
}

// Функция для добавления новой записи
void addElement(Element*& elements, int& size) {
    Element newElement;
    newElement.readFromConsole();

    // Выделение памяти для нового массива
    Element* newElements = new Element[size + 1];
    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    newElements[size] = newElement;

    // Освобождение старой памяти
    delete[] elements;
    elements = newElements;
    ++size;
}

// Функция для изменения записи
void editElement(Element* elements, int size) {
    int index;
    cout << "Введите номер элемента для изменения (0 - " << size - 1 << "): ";
    while (!(cin >> index) || index < 0 || index >= size) {
        cout << "Неверный номер элемента. Введите число от 0 до " << size - 1 << ": ";
        cin.clear();
    }

    cout << "Введите новые данные элемента: ";
    Element replcaceElement;
    replcaceElement.readFromConsole();
    
    elements[index] = replcaceElement;
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");

  int size = 0;
  Element *elements = new Element[size];

  string menu[] = {
      "Чтение из консоли",
      "Чтение из файла",
      "Показать все элементы",
      "Показать все элементы металлы ", 
      };
  int menu_count = sizeof(menu) / sizeof(menu[0]);

  cout << "Начало работы программы" << endl;
  int select = -1;
  do {
    cout << endl << "Меню: " << endl;

    // Выводим меню программы
    for (int i = 0; i < menu_count; i++) {
      cout << i << ". " << (menu[i]) << endl;
    }

    cout << endl
         << "Выберите номер (любое другое число это выход из программы): ";
    if (!(cin >> select)) {
      select = -1;
    }

    switch (select)
    {
    case 0:
        readFromConsole(elements, size);
        break;
    
    default:
        cout << "Выход из приложения" << endl;
        break;
    }

    cout << endl;

  } while (select >= 0 && select < menu_count);

  // Освобождение памяти
  delete[] elements;

  return 0;
}
