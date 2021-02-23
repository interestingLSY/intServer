#pragma once

#include <map>
#include <unordered_map>
#include <set>

#include "base/common.hpp"
#include "block/block.hpp"
#include "world/chunk.hpp"
#include "player/player.hpp"

namespace IntServer{

class World{
	std::map<V2i,Chunk> chunkMap;	// TODO use unordered_map
	std::unordered_map<UUID,Player> playerMap;
public:
	int id;
	string name;
	Difficulty difficulty;

	World( int id , string &name ){
		this->id = id;
		this->name = name;
	}

	V2i InWhichChunk( V3i blockPos ){
		return V2i{
			int( (double)blockPos.x / 16 + 1e-5 ),
			int( (double)blockPos.z / 16 + 1e-5 )
		};
	}

	Chunk& GetChunk_W( V2i chunkPos ){
		if(!chunkMap.count(chunkPos)) Warning("chunk not found",chunkPos);
		return chunkMap[chunkPos];
	}
	Chunk GetChunk( V2i chunkPos ){
		return GetChunk_W(chunkPos);
	}

	Block& GetBlock_W( V3i blockPos ){
		V2i chunkPos = InWhichChunk(blockPos);
		return GetChunk_W(chunkPos).GetBlockFromAbsPos_W(blockPos);
	}
	Block GetBlock( V3i blockPos ){
		return GetBlock_W(blockPos);
	}

	void AddPlayer( const Player &player ){
		playerMap[player.uuid] = player;
	}
	void RemovePlayer( UUID uuid ){
		playerMap.erase(uuid);
	}
	Player& GetPlayer_W( UUID uuid ){
		Assert( playerMap.count(uuid) );
		return playerMap[uuid];
	}
	Player GetPlayer( UUID uuid ){
		return GetPlayer_W(uuid);
	}
};

}

namespace IntServer{
	std::vector<World> worlds;
	namespace Worlds{
		void RegisterWorld( string name ){
			int nowId = worlds.size();
			World nowWorld({
				id: nowId,
				name: name
			});
			worlds.push_back(nowWorld);
		}
		void RegisterWorlds(){
			RegisterWorld("overworld");
		}

		void RemovePlayerFromAllWorlds( UUID uuid ){
			for( World &world : worlds )
				world.RemovePlayer(uuid);
		}
	}
	World& InWhichWorld( Player player ){
		
	}
}
