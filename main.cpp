#include "classes/element.hpp"  // Для работы с классом Element
#include "classes/elements.hpp" // Для работы с массивом Element

using namespace std;


int main() {
  setlocale(LC_ALL, "Russian");

  int size = 0;
  Element *elements = new Element[size];

  string menu[] = {
      "Чтение из консоли",
      "Чтение из файла",
      "Показать все элементы",
      "Показать все элементы металлы ", 
      "Добавить элемент",
      "Изменить элемент",
      "Записать в JSON файл"
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

        case 1:
            readFromJSON(elements, size);
            break;
        
        case 2:
            displayAllElements(elements, size);
            break;

        case 3:
            displayMetals(elements, size);
            break;

        case 4:
            addElement(elements, size);
            break;

        case 5:
            editElement(elements, size);
            break;
        
        case 6:
            writeToJSON(elements, size);
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
