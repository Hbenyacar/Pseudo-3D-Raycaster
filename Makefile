# Compiler
CXX = clang++
CXXFLAGS = -std=c++17 -Wall

# SFML paths (change if your brew prefix is different)
SFML_INCLUDE = /opt/homebrew/opt/sfml/include
SFML_LIB = /opt/homebrew/opt/sfml/lib

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = sfml_app
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -I$(SFML_INCLUDE) -L$(SFML_LIB) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
