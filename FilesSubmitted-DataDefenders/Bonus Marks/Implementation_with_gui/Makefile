# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files and objects
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = main

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run: $(TARGET)
	./$(TARGET)

# Valgrind check target
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all run clean valgrind
