#if !defined(CRUMB_HPP)
#define CRUMB_HPP
#include <iostream>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;

inline int CrumbMain()
{
  std::cout << "Crumb Beta 1" << "\n";
  std::cout << "Type `new` to add a new task\n.";
  std::cout << "Type `exit` to exit and create the config file.\n";

  std::string command;
  json j;

  while (true)
  {
    std::cout << "--> ";
    std::cin >> command;

    if (command == "new")
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

      j[taskName] = obj;
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
