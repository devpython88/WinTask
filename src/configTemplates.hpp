#pragma once // i literally just learnt about this
#include <iostream>
#include "json.hpp"

class Templates {
public:
	static inline std::string basic(){
		nlohmann::json j;
		j["mytask_1"] = nlohmann::json();

		j["mytask_1"]["commands"].push_back("echo Hello!");

		j["mytask_2"] = nlohmann::json();

		j["mytask_2"]["commands"].push_back("echo Hello 2!");

		return j.dump(4);
	}
};