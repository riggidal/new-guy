#ifndef ELEMENTS
#define ELEMENTS

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Для форматирования вывода

#include "classes/element.hpp"  // Для работы с классом Element

void displayAllElements(Element*&, int&);
void readFromConsole(Element*&, int&);
void readFromJSON(Element*&, int&);
void writeToJSON(Element*&, int&);
void addElement(Element*&, int&);
void editElement(Element*&, int&);
void resizeElements(Element*&, int&);


#endif