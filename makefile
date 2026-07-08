CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -Iinclude
TARGET = bin/motor_imagen.exe

SRCS = src/main.cpp \
       src/Programa.cpp \
       src/ControlMotor.cpp \
       src/infraestructura.cpp \
       src/algoritmos_deforestacion.cpp \
       src/algoritmos_estrellas.cpp \
       src/algoritmos_medicina.cpp

OBJS = $(SRCS:src/%.cpp=obj/%.o)

all: directorios $(TARGET)

directorios:
	@if not exist obj mkdir obj
	@if not exist bin mkdir bin

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist obj rmdir /s /q obj
	@if exist bin rmdir /s /q bin

.PHONY: all clean directorios