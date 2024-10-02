SRC := ../src/main.cpp ../src/wintask.h ../src/wintask.cpp
GPP := g++
FLAGS := -O3 -std=c++17
LDFLAGS := 
TARGET := wintask.exe

all:
	$(GPP) -o $(TARGET) $(SRC) $(FLAGS) $(LDFLAGS)	