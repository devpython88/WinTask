#if !defined(WINTASK_H)
#define WINTASK_H
#include <json.hpp>
using json = nlohmann::json;

class WinTask
{
private:
    json file;
    json vars;

public:
    WinTask(json main) : file(main)
    {
        if (file.contains("variables"))
        {
            vars = file["variables"];
        }
    }
    int RunTask(std::string task);
    int ShowInformation(std::string task);
    std::string FormatText(std::string text);
};

#endif // WINTASK_H
