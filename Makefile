CXX = g++
CXXFLAGS = -g -Wall -std=c++11

SRCS = main.cpp console.cpp renderer.cpp
HEADERS = console.h math.h renderer.h vertex.h mesh.h light.h primitives.h
OBJS = $(SRCS:.cpp=.o)

TARGET = ascii_renderer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
