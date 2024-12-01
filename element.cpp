#include "element.hpp"

// Конструктор по умолчанию
Element::Element() : name(""), symbol(""), number(0), type(""), mass(0), electrons("") {}

void Element::readFromConsole(){
    cout << "Введите название элемента: ";
    cin >> name;
    cout << "Введите символ элемента: ";
    cin >> symbol;
    cout << "Введите номер элемента: ";
    while (!(cin >> number) || number <= 0) {
        cout << "Неверный номер элемента. Введите целое число: ";
        cin.clear();
    }
    cout << "Введите тип элемента (metal или non-metal): ";
    while (cin >> type && type != "metal" && type != "non-metal") {
        cout << "Неверный тип элемента. Введите 'metal' или 'non-metal': ";
    }
    cout << "Введите атомную массу элемента: ";
    while (!(cin >> mass) || mass <= 0) {
        cout << "Неверная атомная масса. Введите целое число: ";
        cin.clear();
    }
    cout << "Введите электронную конфигурацию элемента: ";
    cin >> electrons;
}

ifstream& Element::readFromJson(ifstream& stream) {
    json file;

    stream >> file;

    for (int i=0; i < file["count"]; i++)
    {
        json value = file["values"][i];
        
    }

    return stream;
}

ofstream& Element::writeToJson(ofstream& stream){

    return stream;
}

void Element::display(){
    cout << left << setw(20) << name << setw(10) << symbol << setw(10) << number << setw(15) << type << setw(15) << fixed << setprecision(2) << mass << electrons << endl;
}

void Element::shortDisplay(){
    cout << name << "(" << symbol << ")" << endl;
}

bool Element::isType(string t){
    return type == t;
}
