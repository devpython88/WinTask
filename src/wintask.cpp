#include "wintask.h"

int EXITCODE_TASK_NOT_EXIST = 1;
int EXITCODE_SUCCESS = 0;
int EXITCODE_ERROR_IN_TASK = 2;
int EXITCODE_NO_COMMANDS = 3;

int WinTask::RunTask(std::string task)
{
    if (!file.contains(task)){
        return EXITCODE_TASK_NOT_EXIST;
    }

    json taskObject = file[task];

    if (!taskObject.contains("commands")){
        return EXITCODE_NO_COMMANDS;
    }

    std::vector<std::string> commands = taskObject["commands"];

    for (int i=0; i<commands.size(); i++){
        std::string command = commands[i];

        int code = system(command.c_str());
        if (code != 0){
            return EXITCODE_ERROR_IN_TASK;
        }
    }

    return EXITCODE_SUCCESS;
}