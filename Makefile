# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/Cellar/nlohmann-json/3.12.0/include
LDFLAGS = -lcurl

TARGET = Record_My_Brilliancy
SRC = Record_My_Brilliancy.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)