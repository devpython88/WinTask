SRC := ../src/main.cpp ../src/wintask.cpp
HEADERS := ../src/crumb.hpp ../src/wintask.h
GPP := g++
FLAGS := -O3 -std=c++17
LDFLAGS := 
TARGET := wintask.exe

all:
	$(GPP) -o $(TARGET) $(HEADERS) $(SRC) $(FLAGS) $(LDFLAGS)	
