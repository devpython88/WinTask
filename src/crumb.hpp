#if !defined(CRUMB_HPP)
#define CRUMB_HPP
#include <iostream>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;


/* ADD TASK */

inline void AddTask_Crumb(json* j)
{
  std::string taskName;
  std::vector<std::string> taskCommands;

  std::cout << "Task name --> ";
  std::cin >> taskName;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (true)
  {
    std::string cmd;
    std::cout << "Enter command (or ! to end adding commands) -->";

    std::getline(std::cin, cmd);

    if (cmd != "!")
    {
      taskCommands.push_back(cmd);
      continue;
    }

    break;
  }

  json obj;

  obj["commands"] = taskCommands;

  j->emplace(taskName, obj);
}

/* ADD VARIABLE */

inline void AddVar_Crumb(json *j){
  std::string variableName;
  std::string variableValue;
  
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Enter the variable name --> ";
  std::getline(std::cin, variableName); 
 
  std::cout << "Enter the variable value --> ";
  std::getline(std::cin, variableValue);

  if (!j->contains("variables")){
    j->emplace("variables", json{{variableName, variableValue}});
    return;
  }

  j->at("variables").emplace(json{variableName, variableValue});
}








inline int CrumbMain()
{
  std::cout << "Crumb Beta 2" << "\n";
  std::cout << "Type `new` to add a new task.\n";
  std::cout << "Type `var` to add a new variable.\n";
  std::cout << "Type `exit` to exit and create the config file.\n";

  std::string command;
  json j;

  while (true)
  {
    std::cout << "--> ";
    std::cin >> command;

    if (command == "new")
    {
      AddTask_Crumb(&j);
    }

    else if (command == "var"){
      AddVar_Crumb(&j);
    }

    else if (command == "exit")
    {
      std::ofstream f("wintask.json");

      if (!f.is_open())
      {
        f.close();
        std::cerr << "Could not create file.\n";
        return 1;
      }

      f << j.dump(4);
      f.close();
      return 0;
    }
    else
    {
      std::cerr << "Invalid command\n";
    }
  }

  return 0;
}

#endif // CRUMB_HPP
