# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Source files excluding main.cpp for testing
TEST_SRCS = $(filter-out main.cpp, $(wildcard *.cpp))
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Output executable names
TARGET = main
TEST_TARGET = test_exec

# Default target
all: $(TARGET)

# Compile main target
$(TARGET): $(filter-out test.o, $(OBJS))
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(filter-out test.o, $(OBJS))

# Compile test target (ignores main.cpp)
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run test target
run_test: test
	./$(TEST_TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Valgrind check target
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean up object files and executables
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Documentation
docs:
	doxygen Doxyfile
	@echo "Documentation generated in docs/html"

# Clean up documentation
clean_docs:
	rm -rf docs/

# Phony targets
.PHONY: all run clean test run_test valgrind docs clean_docs
