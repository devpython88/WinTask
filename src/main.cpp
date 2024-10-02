#include <iostream>
#include <fstream>
#include <filesystem>
#include "wintask.h"

namespace fs = std::filesystem;

std::string VERSION = "v1.0";

int main(int argc, char *argv[]){
    if (argc == 1){
        return 0;
    }

    std::string action = argv[1];
    if (action == "/run"){
        if (argc == 2){
            std::cerr << "No task name provided.";
            return 1;
        }

        if (!fs::exists("wintask.json")){
            std::cerr << "There is no wintask.json file in the current directory.\n";
            return 1;
        }

        std::ifstream fl("wintask.json");

        if (!fl.is_open()){
            std::cerr << "Error occured while reading config!\n";
            return 1;
        }

        json f;
        fl >> f;

        WinTask winTask(f);
        int code = winTask.RunTask(argv[2]);

        switch (code){
            case 1:
            std::cerr << "The specified task does not exist.\n";
            return 1;

            case 0:
            return 0;

            case 2:
            std::cerr << "Error while running task.\n";
            return 1;

            case 3:
            std::cerr << "No commands to run.\n";
            return 1;
        }
    }

    else if (action == "/?"){
        std::cout << "WinTask " << VERSION << " by devpython88.\n";
    }
    return 0;
}