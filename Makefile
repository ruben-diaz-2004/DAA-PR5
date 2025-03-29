# Makefile for DAA-PRS Project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++23 -Wall -Wextra -I./include

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BIN_DIR)/daa-prs

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up built files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Create necessary directories


# Phony targets
.PHONY: all clean dirs