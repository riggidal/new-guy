#include "elements.hpp"

// !!!
// В следующей лабораторной работе этот файл превратиться в класс контейнер
// !!!

// Отобразить все элементы
void displayAllElements(Element *&elements, int &size){
    cout << "Все элементы:" << endl;

    // Заголовки таблицы с форматированием
    cout << left 
         << setw(20) << "Название " 
         << setw(10) << " Символ " 
         << setw(10) << " Номер " 
         << setw(15) << " Тип " 
         << setw(15) << " Атомная масса " 
         << " Электронная конфигурация " 
         << endl;

    cout << string(100, '-') << endl; // Разделительная линия

    for (int i = 0; i < size; i++)
    {
        elements[i].display();    
    }

    cout << endl;
}

// Заполнение массива через консоль
void readFromConsole(Element *&elements, int &size) {

    cout << "Введите количество элементов: ";
    while (!(cin >> size) || size < 1) {
        cout << "Неверное количество элементов. Повторите: ";
        cin.clear();
    }

    resizeElements(elements, size);

    for (int i = 0; i < size; i++)
    {
        Element newElement;
        newElement.readFromConsole();

        elements[i] = newElement;
    }
    
    cout << "Все элементы добавлены." << endl;
}

// Заполнение массива через файл JSON
void readFromJSON(Element *&elements, int &size) {

    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream stream(filename);
    if (!stream) {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }

    json jsonFile;

    stream >> jsonFile;

    // Изменим размер
    size = jsonFile["count"];
    resizeElements(elements, size);

    for (int i = 0; i < size; i++)
    {
        elements[i] = Element(jsonFile["values"][i]);
    }
    
    cout << "Все элементы добавлены." << endl;
}


// Запись в файл JSON
void writeToJSON(Element *&elements, int &size) {
    string filename;

    cout << "Запись в файл JSON: " << endl;
    cout << "Введите имя файла: ";
    cin >> filename;

    ofstream stream(filename, ios::app);
    if (!stream) {
        cerr << "Ошибка открытия файла: " << filename << endl;
    }

    json jsonFile;

    jsonFile["count"] = size;

    for (int i = 0; i < size; i++)
    {
        jsonFile["values"].push_back(elements[i].getJSON());
    }

    stream << jsonFile.dump(4);
    
    cout << "Все элементы записаны." << endl;
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
void editElement(Element*& elements, int& size) {
    int index;
    cout << "Введите номер элемента для изменения (0 - " << size - 1 << "): ";
    while (!(cin >> index) || index < 0 || index >= size) {
        cout << "Неверный номер элемента. Введите число от 0 до " << size - 1 << ": ";
        cin.clear();
    }

    cout << "Введите новые данные элемента: " << endl;
    Element replcaceElement;
    replcaceElement.readFromConsole();
    
    elements[index] = replcaceElement;
}

// Анулировать массив и указать новый размер
void resizeElements(Element*& elements, int& size) {

    // Очистим предыдущие значния
    delete[] elements;

    // Новый массив
    elements = new Element[size];

}