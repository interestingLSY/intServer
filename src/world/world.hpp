#pragma once

#include <vector>

#include "base/common.hpp"
#include "dim/dim.hpp"
#include "nbt_tags.h"

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

	NBT GetDimTypeNBT(){
		// see https://wiki.vg/Protocol#Join_Game
		using namespace nbt;
		tag_list values;
		for( Dim &dim : dimMap ){
			Debug(dim.properties);
			tag_compound t = {
				{"name", dim.name},
				{"id", tag_int(dim.id)},
				{"elements", tag_compound(dim.properties)}
			};
			values.push_back(tag_compound(t));
		}
		return NBT{
			{"type", "minecraft:dimension_type"},
			{"value", tag_list(values)}
		};
	}
	NBT GetDimCodecNBT(){
		// see https://wiki.vg/Protocol#Join_Game
		using namespace nbt;
		return NBT{
			{"minecraft:dimension_type", GetDimTypeNBT()},
			{"minecraft:worldgen/biome", Biomes::GetWorldgenBiomeNBT()}
		};
	}
};

}

namespace IntServer{
	std::vector<World> worldMap;
	inline World& UnderWhichWorld( EPos ePos ){
		return worldMap[ePos.worldId];
	}
	inline Dim& UnderWhichDim( EPos ePos ){
		return UnderWhichWorld(ePos).dimMap[ePos.dimId];
	}
}

namespace IntServer{
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
						properties: tag_compound{
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
							{"ultrawarm", tag_byte(0) },
							{"has_ceiling", tag_byte(0) }
						}
					}
				}
			});
		}

	}
}
