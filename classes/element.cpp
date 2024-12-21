#include "element.hpp"
// Конструктор по умолчанию
Element::Element() : name(""), symbol(""), number(0), type(""), mass(0), electrons("") {}

Element::Element(json value) : name(value["name"]), symbol(value["symbol"]), number(value["number"]), type(value["type"]), mass(value["mass"]), electrons(value["electrons"]) {}

istream& operator>>(istream& in, Element& el){
    cout << "Введите название элемента: ";
    in >> el.name;

    cout << "Введите символ элемента: ";
    in >> el.symbol;

    cout << "Введите номер элемента: ";
    while (!(in >> el.number) || el.number <= 0) {
        cout << "Неверный номер элемента. Введите целое число: ";
        in.clear();
        in.ignore();
    }
    cout << "Введите тип элемента (metal или non-metal): ";
    while (in >> el.type && el.type != "metal" && el.type != "non-metal") {
        cout << "Неверный тип элемента. Введите 'metal' или 'non-metal': ";
        in.clear();
        in.ignore();
    }
    cout << "Введите атомную массу элемента: ";
    while (!(in >> el.mass) || el.mass <= 0) {
        cout << "Неверная атомная масса. Введите целое число: ";
        in.clear();
        in.ignore();
    }
    cout << "Введите электронную конфигурацию элемента: ";
    in >> el.electrons;

    return in;
}

ostream& operator<<(ostream& out, Element& el){
    out
        << "Наименование:\t" << el.name << endl
        << "Символ:\t\t" << el.symbol << endl
        << "Номер:\t\t" << el.number << endl
        << "Тип:\t\t" << el.type << endl
        << "Масса\t\t" << fixed << setprecision(1) << el.mass << endl
        << "Элекронная конфигурация: " << el.electrons << endl;
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

bool Element::operator==(Element& el)
{
    return this->getJSON() == el.getJSON();
}
