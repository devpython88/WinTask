#pragma once
#include <json.hpp>
using json = nlohmann::json;

class WinTask
{
private:
    json vars;
    json functions;

public:
    json file;
    WinTask(json main) : file(main)
    {
        if (file.contains("variables"))
        {
            vars = file["variables"];
        }

        if (file.contains("functions"))
        {
            functions = file["functions"];
        }
        
    }
    int RunTask(std::string task, json fl);
    int ShowInformation(std::string task);
    std::string FormatText(std::string text);
    void CallFunction(std::string functionName);
};
