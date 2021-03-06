#pragma once

#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>
#include <cstring>

#include "base/io/log.hpp"
#include "base/math/vec.hpp"
#include "config/config.hpp"
#include "nbt_tags.h"

namespace IntServer{

#define elif else if

typedef unsigned char byte;
typedef long long ll;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned long long UUID;	// yes!
typedef int EID;	// entity ID
typedef nbt::tag_compound NBT;
using JSON = nlohmann::json;
using std::string;

void _AssertFail( const char *expression , const char *file , int line ){
	Critical("Assertion Failed!");
	Critical("Expression:",expression);
	Critical("At file",file);
	Critical("At line",line);
	// exit(0);
}
#define Assert(expr) (static_cast<bool>(expr) ? void(0) : _AssertFail(#expr,__FILE__,__LINE__))

inline UUID GenerateNewUUID(){
	return static_cast<UUID>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}
inline EID GenerateNewEID(){
	static int nowId = 233;
	return nowId++;
}

enum class Difficulty : int {
	PEACEFUL = 0,
	EASY = 1,
	NORMAL = 2,
	HARD = 3
};

enum class Gamemode : int {
	SURVIVAL = 0,
	CREATIVE = 1,
	ADVENTURE = 2,
	SPECTATOR = 3
};

struct EPos{	// Entity pos
	int worldId;
	int dimId;
	V3d pos;
};

}
