CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -Iinclude
TARGET = bin/motor_imagen

# Buscamos todos los archivos fuente en la carpeta src/
SRCS = src/main.cpp \
       src/Programa.cpp \
       src/ControlMotor.cpp \
       src/infraestructura.cpp \
       src/algoritmos_deforestacion.cpp \
       src/algoritmos_estrellas.cpp \
       src/algoritmos_medicina.cpp

# Reemplazamos 'src/' por 'obj/' y '.cpp' por '.o'
OBJS = $(SRCS:src/%.cpp=obj/%.o)

all: directorios $(TARGET)

directorios:
	@mkdir -p obj bin

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regla para compilar cada .cpp en su respectivo .o dentro de obj/
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj bin

.PHONY: all clean directorios