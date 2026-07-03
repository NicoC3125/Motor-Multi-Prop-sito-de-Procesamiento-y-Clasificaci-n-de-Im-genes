CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I.
TARGET = motor_imagen
SRCS = main.cpp src/infraestructura.cpp src/algoritmos_deforestacion.cpp src/algoritmos_estrellas.cpp src/algoritmos_medicina.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean