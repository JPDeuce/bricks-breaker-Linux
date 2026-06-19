CXX    := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g
LDFLAGS :=
OBJS   := Main.o Game.o Ball.o Box.o BaseObject.o Console.o
TARGET := bricks

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

Main.o: Main.cpp Common.h Game.h
Game.o: Game.cpp Common.h Game.h
Ball.o: Ball.cpp Common.h Ball.h
Box.o:  Box.cpp  Common.h Box.h
BaseObject.o: BaseObject.cpp Common.h BaseObject.h
Console.o: Console.cpp Common.h Console.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
