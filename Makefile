CXX = g++
CXXFLAGS = -std=c++17 -I. -lstdc++fs
LDFLAGS = -lcurl

BIN_DIR = bin
SRC_DIR = src

MAIN_SRC = $(SRC_DIR)/Record_My_Brilliancy.cpp
MAIN_BIN = $(BIN_DIR)/Record_My_Brilliancy

STREAK_SRC = generate_streak.cpp
STREAK_BIN = $(BIN_DIR)/generate_streak

all: $(MAIN_BIN) streak

$(MAIN_BIN): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

$(STREAK_BIN): $(STREAK_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

streak: $(STREAK_BIN)
	./$(STREAK_BIN)

clean:
	rm -f $(BIN_DIR)/*
	rm -f _includes/streak.html
