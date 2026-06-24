CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -Wextra -g
RELEASEFLAGS := -std=c++11 -Wall -Wextra -O2 -DNDEBUG
LDFLAGS   :=
OBJS      := Main.o Game.o Ball.o Box.o BaseObject.o Console.o
TARGET    := bricks
TEST_SRC  := tests/test_game.cpp
TEST_OBJS := test_game.o Game.o Ball.o Box.o BaseObject.o Console.o
TEST_TARGET := test_game

.PHONY: all release test clean

all: $(TARGET)

release: CXXFLAGS = $(RELEASEFLAGS)
release: $(TARGET)
	strip $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): CXXFLAGS = -std=c++11 -Wall -Wextra -g
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_game.o: $(TEST_SRC) Common.h Game.h Ball.h Box.h BaseObject.h Console.h
	$(CXX) -std=c++11 -Wall -Wextra -g -I. -c -o $@ $<

Main.o: Main.cpp Common.h Game.h
Game.o: Game.cpp Common.h Game.h
Ball.o: Ball.cpp Common.h Ball.h
Box.o:  Box.cpp  Common.h Box.h
BaseObject.o: BaseObject.cpp Common.h BaseObject.h
Console.o: Console.cpp Common.h Console.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_OBJS) $(TEST_TARGET)
