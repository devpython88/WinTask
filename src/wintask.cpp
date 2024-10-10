#include "wintask.h"
#include <iostream>
#include <regex>

int EXITCODE_TASK_NOT_EXIST = 1;
int EXITCODE_SUCCESS = 0;
int EXITCODE_ERROR_IN_TASK = 2;
int EXITCODE_NO_COMMANDS = 3;

int WinTask::RunTask(std::string task, json fl)
{
    if (!fl.contains(task))
    {
        return EXITCODE_TASK_NOT_EXIST;
    }

    json taskObject = fl[task];

    if (!taskObject.contains("commands"))
    {
        return EXITCODE_NO_COMMANDS;
    }

    std::vector<std::string> commands = taskObject["commands"];

    for (int i = 0; i < commands.size(); i++)
    {
        std::string command = commands[i];

        std::string newCmd = FormatText(command);

        if (newCmd == "") continue;

        int code = system(newCmd.c_str());
        if (code != 0)
        {
            return EXITCODE_ERROR_IN_TASK;
        }
    }

    return EXITCODE_SUCCESS;
}

int WinTask::ShowInformation(std::string task)
{
    if (!file.contains(task))
    {
        return EXITCODE_TASK_NOT_EXIST;
    }

    json taskObject = file[task];

    std::cout << "<----------------------------->" << "\n";

    std::string taskDescription = "No description specified.";
    std::string taskPurpose = "No purpose specified.";

    if (taskObject.contains("description"))
    {
        taskDescription = taskObject["description"];
    }

    if (taskObject.contains("purpose"))
    {
        taskPurpose = taskObject["purpose"];
    }

    std::cout << "| Task description -- " << taskDescription << "\n";
    std::cout << "| Task purpose -- " << taskPurpose << "\n";

    std::vector<std::string> commands = taskObject["commands"];

    if (commands.empty())
        return 0;

    std::cout << "| Task commands :: " << "\n";
    for (std::string command : commands)
    {
        std::cout << "< -- " << command << "\n";
    }
    std::cout << "<----------------------------->" << "\n";

    return EXITCODE_SUCCESS;
}

std::string WinTask::FormatText(std::string text)
{
    std::string newString = text;

    for (auto &kvp : vars.items())
    {
        std::string pattern = "\\$\\{" + kvp.key() + "\\}";
        std::string val = kvp.value().dump();

        std::string replacement;
        if (kvp.value().is_string())
        {
            replacement = kvp.value();
        }
        else
        {
            replacement = kvp.value().dump();
        }

        newString = std::regex_replace(newString, std::regex(pattern), replacement);
    }

    for (auto &fnc : functions.items()){
        std::string pattern = "@" + fnc.key();
        int timesCalled;

        if ((timesCalled = newString.find(pattern)) != std::string::npos){
            newString = "";
            int i = 1;

            do {
                CallFunction(fnc.key());
                i++;
            } while (i <= timesCalled);
        }
    }

    return newString;
}

void WinTask::CallFunction(std::string functionName)
{
    RunTask(functionName, functions);
}
