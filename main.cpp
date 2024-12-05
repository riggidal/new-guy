#include "classes/elements.hpp"
#include <iostream>
#include <functional>
#include <unordered_map>

class Application {
private:
    ElementContainer container;

    std::unordered_map<int, std::function<void()>> menuOptions;
    std::vector<std::string> menuText;

    void initializeMenu() {
        menuText = {
            "Чтение из консоли",
            "Чтение из файла",
            "Показать все элементы",
            "Показать все элементы металлы",
            "Добавить элемент",
            "Изменить элемент",
            "Записать в JSON файл",
            "Найти элемент по массе"
        };

        menuOptions = {
            {0, [this]() { readFromConsole(); }},
            {1, [this]() { readFromJSON(); }},
            {2, [this]() { displayAllElements(); }},
            {3, [this]() { displayMetals(); }},
            {4, [this]() { addElement(); }},
            {5, [this]() { editElement(); }},
            {6, [this]() { writeToJSON(); }},
            {7, [this]() { findByMass(); }}
        };
    }

    void readFromConsole() {
        Element element;
        element.readFromConsole();
        container.addElement(element);
    }

    void readFromJSON() {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        container.readFromJSON(filename);
    }

    void displayAllElements() {
        container.displayElements();
    }

    void displayMetals() {
        container.displayMetals();
    }

    void addElement() {
        Element element;
        element.readFromConsole();
        container.addElement(element);
    }

    void editElement() {
        int index;
        std::cout << "Введите номер элемента для изменения (0 - " << container.getSize() - 1 << "): ";
        while (!(std::cin >> index) || index >= container.getSize()) {
            std::cout << "Неверный индекс. Повторите ввод: ";
        }
        Element updatedElement;
        updatedElement.readFromConsole();
        container.editElement(index, updatedElement);
    }

    void writeToJSON() {
        std::string filename;
        std::cout << "Введите имя файла для записи: ";
        std::cin >> filename;
        container.writeToJSON(filename);
    }

    void findByMass() {
        int mass = 0;
        cout << "Введите массу элемента: ";
        while (!(cin >> mass) || mass <= 0) {
            cout << "Неверная масса. Введите целое число: ";
            cin.clear();
            cin.ignore();
        }
        container.findElementByMass(mass);
    }

public:
    Application() {
        initializeMenu();
    }

    void run() {
        int select = -1;
        do {
            displayMenu();
            std::cout << "Выберите номер (любое другое число для выхода): ";
            if (!(std::cin >> select)) {
                select = -1;
            }
            auto it = menuOptions.find(select);
            if (it != menuOptions.end()) {
                it->second(); // Invoke the selected menu option
            } else {
                std::cout << "Выход из программы." << std::endl;
                break;
            }
            std::cout << std::endl;
        } while (select >= 0);
    }

    void displayMenu() {
        std::cout << "\nМеню:\n";
        for (size_t i = 0; i < menuText.size(); ++i) {
            std::cout << i << ". " << menuText[i] << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Application app;
    app.run();
    return 0;
}
