CXX = clang++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp Player.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = raycaster

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
