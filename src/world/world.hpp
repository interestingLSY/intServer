#pragma once

#include <vector>

#include "base/common.hpp"
#include "dim/dim.hpp"
#include "nbt_tags.hpp"

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

	void GetDimCodec(){

		for( Dim &dim : dimMap ){

		}
	}
};

}

namespace IntServer{
	std::vector<World> worldMap;
	namespace Worlds{
		void RegisterDefaultWorld( Difficulty difficulty ){
			using namespace nbt;
			worldMap.push_back(World{
				id: static_cast<int>(worldMap.size()),
				name: "defaultWorld",
				dimMap: std::vector<Dim>{
					Dim{
						id: 0,
						name: "overworld",
						difficulty: difficulty,
						property: tag_compound{
							{"piglin_safe", tag_byte(0) },
							{"natural", tag_byte(1) },
							{"ambient_light", tag_float(0.0f) },
							{"infiniburn", "minecraft:infiniburn_overworld" },
							{"respawn_anchor_works", tag_byte(0) },
							{"has_skylight", tag_byte(1) },
							{"bed_works", tag_byte(1) },
							{"effects", "minecraft:overworld" },
							{"has_raids", tag_byte(1) },
							{"logical_height", tag_int(256) },
							{"coordinate_scale", tag_float(1.0d) },
							{"ultrawarm": tag_byte(0) },
							{"has_ceiling": tag_byte(0) }
						}
					},
					// Dim{
					// 	id: 1,
					// 	name: "nether",
					// 	difficulty: difficulty,
					// },
					// Dim{
					// 	id: 2,
					// 	name: "the_end",
					// 	difficulty: difficulty,
					// }
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
