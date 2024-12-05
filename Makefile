# Определяем компилятор и флаги
CC = g++
CFLAGS = -c -Wall -g 

# Исходные файлы
SOURCES = main.cpp classes/element.cpp classes/elements.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Исполняемый файл
EXECUTABLE = main

# Правило по умолчанию
all: $(EXECUTABLE)

# Линковка объектных файлов в исполняемый файл
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Компиляция .cpp в .o
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# Очистка временных файлов
clean:
	rm -rf *.o $(EXECUTABLE)