# Compiler and flags
CXX = gcc
CXXFLAGS = -lm -std=c++11

# Executable name
TARGET = output

# Source and object files
SRC = src/main.c
OBJ = $(SRC:.c=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Utility commands
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
