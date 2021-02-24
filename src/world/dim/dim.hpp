#pragma once

#include <map>
#include <unordered_map>
#include <set>

#include "base/common.hpp"
#include "chunk/chunk.hpp"
#include "player.hpp"
#include "nbt_tags.h"

namespace IntServer{

class Dim{
protected:
	std::map<V2i,Chunk> chunkMap;	// TODO use unordered_map
	std::unordered_map<UUID,Player> playerMap;
public:
	int id;
	string name;
	Difficulty difficulty;
	NBT properties;

	Dim( int id , const string name , Difficulty difficulty , const NBT properties ){
		this->id = id;
		this->name = name;
		this->difficulty = difficulty;
		this->properties = properties;
	}

	Chunk& GetChunk( V2i chunkPos ){
		if(!chunkMap.count(chunkPos)) Warning("chunk not found",chunkPos);
		return chunkMap[chunkPos];
	}

	Block& GetBlock( V3i blockPos ){
		return GetChunk(UnderWhichChunkCoor(blockPos)).GetBlock(blockPos);
	}

	Biome& GetBiome( V3i biomePos ){
		return GetChunk(UnderWhichChunkCoor(biomePos)).GetBiome(biomePos);
	}

	void AddPlayer( const Player &player ){
		playerMap[player.uuid] = player;
	}
	void RemovePlayer( UUID uuid ){
		playerMap.erase(uuid);
	}
	Player& GetPlayer( UUID uuid ){
		Assert( playerMap.count(uuid) );
		return playerMap[uuid];
	}
};

}
