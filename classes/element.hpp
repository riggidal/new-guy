#ifndef ELEMENT
#define ELEMENT

#include <fstream>
#include <iostream>
#include <string>

#include "../libraries/json.hpp"

using namespace std;
using namespace nlohmann;

class Element {
    private:
        string name;         // Название элемента
        string symbol;       // Символ элемента
        int number;          // Номер в таблице
        string type;         // Тип элемента
        int mass;            // Атомная масса
        string electrons;    // Электронная конфигурация

    public:

        Element();
        Element(json);


        void readFromConsole();

        void display();
        void shortDisplay();

        // Гетеры
        string getName() { return name; };
        string getSymbol() { return symbol; };
        int getNumber() { return number; };
        string getType() { return type; };
        int getMass() { return mass; };
        string getElectrons() { return electrons; };

        json getJSON();
        
        // Сетеры
        void setName(string value) { name = value; };
        void setSymbol(string value) { symbol = value; };
        void setNumber(int value) { number = value; };
        void setType(string value) { type = value; };
        void setMass(int value) { mass = value; };
        void setElectrons(string value) { electrons = value; };

        bool isType(string);
};

#endif