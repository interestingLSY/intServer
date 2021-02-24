#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>

#include "base/common.hpp"
#include "base/network/networkMain.hpp"
#include "world/world.hpp"
#include "nbt_tags.h"
#include "io/stream_reader.h"
#include "io/izlibstream.h"

namespace IntServer{

	namespace IntServerMain{
		void Greet(){
			// something useless but fun
			Notice("Welcome to intServer, a high performance minecraft server.");
			Notice("自豪地使用 intServer.");
			constexpr int greetings_length = 8;
			constexpr char greetings[greetings_length][64] = {
				"Wish there is no bug...",
				"Give me a star on github, plz. =w=",
				"My engligh are nor very well, sorey...",
				"Try out the PaperMC server!",
				"The server is going to explode in 10 seconds...",
				"Do you have a girlfriend?",
				"HELP DEV!",
				"PY, have you finished your chemistry homework?"
			};
			srand((int)time(0));
			Notice(greetings[rand()%greetings_length]);
		}

		int main( int argc , char *argv[] ){
			Greet();

			std::thread networkMainThread(IntServer::Network::StartTCPServer,14250);
			networkMainThread.detach();

			Biomes::RegisterDefaultBiomes();
			Worlds::RegisterDefaultWorld(Difficulty::HARD);

			while(1){
				sleep(10);
			}

			return 0;
		}
	}
}

int main( int argc, char *argv[] ){
	return IntServer::IntServerMain::main(argc,argv);
}
