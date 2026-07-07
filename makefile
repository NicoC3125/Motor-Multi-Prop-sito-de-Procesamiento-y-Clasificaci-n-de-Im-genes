CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -I.
TARGET = motor_imagen

SRCS = main.cpp \
       Programa.cpp \
       ControlMotor.cpp \
       infraestructura.cpp \
       algoritmos_deforestacion.cpp \
       algoritmos_estrellas.cpp \
       algoritmos_medicina.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean