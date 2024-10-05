#include <iostream>
#include <fstream>
#include <filesystem>
#include "wintask.h"
#include "crumb.hpp"

namespace fs = std::filesystem;

std::string VERSION = "v1.52";

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

		if (!fs::exists("wintask.json"))
		{
			std::cerr << "There is no wintask.json file in the current directory.\n";
			return 1;
		}

		std::ifstream fl("wintask.json");

		if (!fl.is_open())
		{
			std::cerr << "Error occured while reading config!\n";
			fl.close();
			return 1;
		}

		json f;
		fl >> f;

		fl.close();

		WinTask winTask(f);
		int code = winTask.RunTask(argv[2]);

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

		if (!fs::exists("wintask.json"))
		{
			std::cerr << "There is no wintask.json file in the current directory.\n";
			return 1;
		}

		std::ifstream fl("wintask.json");

		if (!fl.is_open())
		{
			std::cerr << "Error occured while reading config!\n";
			fl.close();
			return 1;
		}

		json f;
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
		if (!fs::exists("wintask.json"))
		{
			std::cerr << "There is no wintask.json file in the current directory.\n";
			return 1;
		}

		std::ifstream fl("wintask.json");

		if (!fl.is_open())
		{
			std::cerr << "Error occured while reading config!\n";
			fl.close();
			return 1;
		}

		json f;
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

	else if (action == "/new")
	{
		return CrumbMain();
	}
	return 0;
}