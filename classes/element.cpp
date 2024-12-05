#include "element.hpp"
// Конструктор по умолчанию
Element::Element() : name(""), symbol(""), number(0), type(""), mass(0), electrons("") {}

Element::Element(json value) : name(value["name"]), symbol(value["symbol"]), number(value["number"]), type(value["type"]), mass(value["mass"]), electrons(value["electrons"]) {}

void Element::readFromConsole(){
    cout << "Введите название элемента: ";
    cin >> name;

    cout << "Введите символ элемента: ";
    cin >> symbol;

    cout << "Введите номер элемента: ";
    while (!(cin >> number) || number <= 0) {
        cout << "Неверный номер элемента. Введите целое число: ";
        cin.clear();
        cin.ignore();
    }
    cout << "Введите тип элемента (metal или non-metal): ";
    while (cin >> type && type != "metal" && type != "non-metal") {
        cout << "Неверный тип элемента. Введите 'metal' или 'non-metal': ";
        cin.clear();
        cin.ignore();
    }
    cout << "Введите атомную массу элемента: ";
    while (!(cin >> mass) || mass <= 0) {
        cout << "Неверная атомная масса. Введите целое число: ";
        cin.clear();
        cin.ignore();
    }
    cout << "Введите электронную конфигурацию элемента: ";
    cin >> electrons;
}

void Element::display(){
    cout
        << "Наименование:\t" << name << endl
        << "Символ:\t\t" << symbol << endl
        << "Номер:\t\t" << number << endl
        << "Тип:\t\t" << type << endl
        << "Масса\t\t" << fixed << setprecision(1) << mass << endl
        << "Элекронная конфигурация: " << electrons << endl;
}

void Element::shortDisplay(){
    cout << name << "(" << symbol << ")" << endl;
}

bool Element::isType(string t){
    return type == t;
}

json Element::getJSON(){
    json value;
    value["name"] = name;
    value["symbol"] = symbol;
    value["number"] = number;
    value["mass"] = mass;
    value["electrons"] = electrons;

    return value;
}
