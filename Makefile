CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCS = main.cpp Game.cpp Player.cpp Coin.cpp Enemy.cpp PatrolEnemy.cpp ChaseEnemy.cpp
TARGET = CollectAndEscape

# Adjust Raylib paths if needed for Windows (MinGW) / Linux / macOS
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TARGET).exe
