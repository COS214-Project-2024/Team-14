# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Source files and objects
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = main

# Default target
all: $(TARGET)

# Compile target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

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

# Documentation
docs:
	doxygen Doxyfile
	@echo "Documentation generated in docs/html"

# Clean up documentation
clean_docs:
	rm -rf docs/

# Phony targets
.PHONY: all run clean valgrind docs clean_docs
