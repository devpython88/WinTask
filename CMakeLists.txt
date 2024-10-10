cmake_minimum_required(VERSION 3.5)
project(WinTask)

set(CMAKE_CXX_STANDARD 17)

add_executable(wintask src/main.cpp src/configTemplates.hpp src/wintask.cpp src/crumb.hpp src/wintask.h src/json.hpp)