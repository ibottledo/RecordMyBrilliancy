CXX = g++
CXXFLAGS = -std=c++17 -I.
LDFLAGS = -lstdc++fs -lcurl

BIN_DIR = bin
SRC_DIR = src

MAIN_SRC = $(SRC_DIR)/Record_My_Brilliancy.cpp
MAIN_BIN = $(BIN_DIR)/Record_My_Brilliancy

STREAK_SRC = $(SRC_DIR)/generate_streak.cpp
STREAK_BIN = $(BIN_DIR)/generate_streak

all: $(BIN_DIR) $(MAIN_BIN) streak

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(MAIN_BIN): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

$(STREAK_BIN): $(STREAK_SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

streak: $(STREAK_BIN)
	./$(STREAK_BIN)

clean:
	rm -f $(BIN_DIR)/*
	rm -f _includes/streak.html
