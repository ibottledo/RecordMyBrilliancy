CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/Cellar/nlohmann-json/3.12.0/include
LDFLAGS = -lcurl -lstdc++fs

SRC = src/Record_My_Brilliancy.cpp
TARGET = bin/Record_My_Brilliancy

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)
