#include <iostream>
#include <filesystem>
#include "wintask.h"
#include "crumb.hpp"
#include "configTemplates.hpp"

namespace fs = std::filesystem;

std::string VERSION = "v1.7";

std::ifstream getConfig(std::string configFilePath, int argc, char *argv[])
{
	if (!fs::exists(configFilePath))
	{
		std::cerr << "The specified config file `" + configFilePath + "` does not exist.\n";
		exit(1);
	}

	
	std::ifstream fl(configFilePath);

	if (!fl.is_open())
	{
		std::cerr << "Error occured while reading config!\n";
		fl.close();
		exit(1);
	}

	return fl;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		return 0;
	}

	std::string action = argv[1];
	if (action == "/run")
	{
		if (argc == 2)
		{
			std::cerr << "No task name provided.";
			return 1;
		}

		std::string configFilePath = "wintask.json";

		if (argc == 4) configFilePath = argv[3];

		json f;

		std::ifstream fl = getConfig(configFilePath, argc, argv);
		fl >> f;

		fl.close();

		WinTask winTask(f);
		int code = winTask.RunTask(argv[2], winTask.file);

		switch (code)
		{
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

	else if (action == "/info")
	{
		if (argc == 2)
		{
			std::cerr << "No task name provided.";
			return 1;
		}

		std::string configFilePath = "wintask.json";

		if (argc == 4) configFilePath = argv[3];

		json f;

		std::ifstream fl = getConfig(configFilePath, argc, argv);

		fl >> f;
		fl.close();

		WinTask winTask(f);

		if (winTask.ShowInformation(argv[2]) == 1)
		{
			std::cerr << "The specified task does not exist.\n";
			return 1;
		}
	}

	else if (action == "/list")
	{	
		std::string configFilePath = "wintask.json";

		if (argc == 3) configFilePath = argv[2];

		json f;

		std::ifstream fl = getConfig(configFilePath, argc, argv);

		fl >> f;

		fl.close();

		std::cout << "<-------------------------------------->\n";
		for (auto kvp : f.items())
		{
			std::cout << "< " << kvp.key() << "\n";
		}
		std::cout << "<-------------------------------------->\n";
	}

	else if (action == "/?")
	{
		std::cout << "WinTask " << VERSION << " by devpython88.\n";
	}

	else if (action == "/gen"){
		if (argc == 2){
			std::cerr << "No template provided.\n";
			std::cerr << "Templates: basic\n";
			return 1;
		}
		std::ofstream file("wintask.json");

		if (!file.is_open()){
			std::cerr << "Unable to create wintask.json\n";
			return 1;
		}

		file << Templates::basic();
		file.close();
	}

	else if (action == "/new")
	{
		return CrumbMain();
	}
	return 0;
}