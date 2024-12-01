#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Для форматирования вывода

using namespace std;

// Определяем структуру для химического элемента
struct Element {
    string name;         // Название элемента
    string symbol;       // Символ элемента
    int number;          // Номер в таблице
    string type;         // Тип элемента
    int mass;            // Атомная масса
    string electrons;    // Электронная конфигурация
};

// Функция для чтения данных из файла
int readElementsFromFile(const string& filename, Element*& elements) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return 0;
    }

    int count;
    file >> count; // Считываем количество элементов

    elements = new Element[count];

    for (int i = 0; i < count; ++i) {
        file >> elements[i].name >> elements[i].symbol >> elements[i].number >> elements[i].type >> elements[i].mass >> elements[i].electrons;
    }
    file.close();
    return count; // Возвращаем количество считанных элементов
}

// Функция для записи данных в файл
void writeElementsToFile(const string& filename, const Element* elements, int size) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    file << size << endl; // Записываем количество элементов

    for (int i = 0; i < size; ++i) {
        file << elements[i].name << " " << elements[i].symbol << " " << elements[i].number << " " << elements[i].type << " " << elements[i].mass << " " << elements[i].electrons << endl;
    }
    file.close();
}

// Функция для вывода всех элементов
void printAllElements(const Element* elements, int size) {
    cout << "Все элементы:" << endl;
    cout << left << setw(20) << "Название" << setw(10) << "Символ" << setw(10) << "Номер" << setw(15) << "Тип" << setw(15) << "Атомная масса" << "Электронная конфигурация" << endl;
    for (int i = 0; i < size; ++i) {
        cout << left << setw(20) << elements[i].name << setw(10) << elements[i].symbol << setw(10) << elements[i].number << setw(15) << elements[i].type << setw(15) << fixed << setprecision(2) << elements[i].mass << elements[i].electrons << endl;
    }
}

// Функция для поиска элемента по атомной массе
void findElementByMass(const Element* elements, int size, int mass) {
    for (int i = 0; i < size; ++i) {
        if (elements[i].mass == mass) {
            cout << "Найден элемент: " << elements[i].name << " (" << elements[i].symbol << ")" << endl << endl;
            return;
        }
    }
    cout << "Элемент с атомной массой " << mass << " не найден." << endl;
}

// Функция для вывода всех металлов
void printMetals(const Element* elements, int size) {
    cout << "Металлы в массиве:" << endl;
    bool found = false; // Флаг для проверки наличия металлов
    for (int i = 0; i < size; ++i) {
        if (elements[i].type == "metal") {
            cout << elements[i].name << " (" << elements[i].symbol << ")" << endl;
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
    cout << "Введите название элемента: ";
    cin >> newElement.name;
    cout << "Введите символ элемента: ";
    cin >> newElement.symbol;
    cout << "Введите номер элемента: ";
    while (!(cin >> newElement.number) || newElement.number <= 0) {
        cout << "Неверный номер элемента. Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите тип элемента (metal или non-metal): ";
    while (cin >> newElement.type && newElement.type != "metal" && newElement.type != "non-metal") {
        cout << "Неверный тип элемента. Введите 'metal' или 'non-metal': ";
    }
    cout << "Введите атомную массу элемента: ";
    while (!(cin >> newElement.mass) || newElement.mass <= 0) {
        cout << "Неверная атомная масса. Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите электронную конфигурацию элемента: ";
    cin >> newElement.electrons;

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите новое название элемента: ";
    cin >> elements[index].name;
    cout << "Введите новый символ элемента: ";
    cin >> elements[index].symbol;
    cout << "Введите новый номер элемента: ";
    while (!(cin >> elements[index].number) || elements[index].number <= 0) {
        cout << "Неверный номер элемента. Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите новый тип элемента (metal или non-metal): ";
    while (cin >> elements[index].type && elements[index].type != "metal" && elements[index].type != "non-metal") {
        cout << "Неверный тип элемента. Введите 'metal' или 'non-metal': ";
    }
    cout << "Введите новую атомную массу элемента: ";
    while (!(cin >> elements[index].mass) || elements[index].mass <= 0) {
        cout << "Неверная атомная масса. Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Введите новую электронную конфигурацию элемента: ";
    cin >> elements[index].electrons;
}

// Главная функция
int main() {
    setlocale(LC_ALL, "Russian");

    // Чтение данных из файла
    int size = 0;
    Element* elements = nullptr;
    size = readElementsFromFile("elements.txt", elements);
    if (size == 0) {
        return 1; // Выход, если не удалось прочитать данные
    }

    // Вывод всех элементов
    printAllElements(elements, size);

    // Поиск элемента по атомной массе
    int massToFind;
    cout << "Введите атомную массу для поиска: ";
    if (!(cin >> massToFind)) { // Проверка корректности ввода
        cout << "Ошибка ввода! Введите корректное значение!" << endl;
        delete[] elements; // Освобождение памяти в случае ошибки
        return 1;
    }
    findElementByMass(elements, size, massToFind);

    // Вывод металлов
    printMetals(elements, size);

    // Запрос на изменение или добавление записей
    char choice;
    cout << "Хотите внести изменения или добавить новые записи? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        char action;
        cout << "Введите 'a' (англ.) для добавления новой записи или 'e' (англ.) для изменения существующей записи: ";
        cin >> action;
        if (action == 'a' || action == 'A') {
            addElement(elements, size);
        }
        else if (action == 'e' || action == 'E') {
            editElement(elements, size);
        }
        else {
            cout << "Неверный выбор." << endl;
        }
    }

    // Вывод всех элементов после изменений
    printAllElements(elements, size);

    // Запись данных в файл
    writeElementsToFile("elements.txt", elements, size);

    // Освобождение памяти после завершения работы с массивом
    delete[] elements;

    return 0;
}
