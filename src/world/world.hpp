#pragma once

#include <vector>
#include "dim/dim.hpp"

namespace IntServer{

class World{
public:
	int id;
	string name;
	std::vector<Dim> dimMap;

	Dim& GetDim( int dimId ){
		return dimMap[dimId];
	}

	Chunk& GetChunk( int dimId , V2i chunkPos ){
		return GetDim(dimId).GetChunk(chunkPos);
	}

};

}

namespace IntServer{
	std::vector<World> worldMap;
	namespace Worlds{
		void RegisterDefaultWorld(){
			worldMap.push_back(World{
				id: static_cast<int>(worldMap.size()),
				name: "defaultWorld",
				dimMap: std::vector<Dim>{
					Dim{
						id: 0,
						name: "overworld"
					},
					Dim{
						id: 1,
						name: "nether"
					},
					Dim{
						id: 2,
						name: "the_end"
					}
				}
			});
		}

	}
}

namespace IntServer{
	inline World& UnderWhichWorld( EPos ePos ){
		return worldMap[ePos.worldId];
	}
	inline Dim& UnderWhichDim( EPos ePos ){
		return UnderWhichWorld(ePos).dimMap[ePos.dimId];
	}
}
