#pragma once

#include "base/common.hpp"

namespace IntServer{

class Player{
public:
	UUID uuid;
	string name;
	EntityPos pos;
	Gamemode gamemode;
	EID eid;

	// for world.set<Player>
	inline bool operator==( const Player &y )const{
		return uuid == y.uuid;
	}
	inline bool operator<( const Player &y )const{
		return uuid < y.uuid;
	}
};

}
