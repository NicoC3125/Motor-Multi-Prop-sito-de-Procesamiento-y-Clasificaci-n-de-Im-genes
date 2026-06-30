CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I.
TARGET = motor_imagen
SRCS = main.cpp infraestructura.cpp algoritmos_deforestacion.cpp algoritmos_estrellas.cpp algoritmos_medicina.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean