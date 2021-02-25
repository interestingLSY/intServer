#pragma once

#include <fstream>
#include <istream>
#include "json.hpp"

namespace IntServer{

nlohmann::json serverConfig;

namespace Config{
	void ReadConfig(){
		std::ifstream is;
		is.open("config.json");
		if(!is.is_open())
			Critical("Config.json not found QAQ");
		is >> serverConfig;
		is.close();
	}
}

}
