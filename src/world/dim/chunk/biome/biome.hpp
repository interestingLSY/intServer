#pragma once

#include "base/common.hpp"
#include "nbt_tags.h"

namespace IntServer{

enum class BiomeType : int{
	OCEAN,
	PLAINS
};

class BiomeProperties{
public:
	string name;
	id id;

	string precipitation;
	float depth;
	float temperature;
	float scale;
	float downfall;
	string category;

	int effect_sky_color;
	int effect_water_fog_color;
	int effect_fog_color;
	int effect_water_color;
	// 这里还有一些属性没写
	// 详见 https://wiki.vg/Protocol#Join_Game

	NBT GetBiomePropertiesNBT(){
		using namespace nbt;
		return NBT{
			{"name", name},
			{"id", tag_int(id) },
			{"elements", tag_compound{
				{"precipitation", precipitation},
				{"depth", depth},
				{"temperature", temperature},
				{"scale", scale},
				{"downfall", downfall},
				{"category", category},
				{"effects", tag_compound{
					{"sky_color", effect_sky_color},
					{"water_fog_color", effect_water_fog_color},
					{"fog_color", effect_fog_color},
					{"water_color", effect_water_color}
				}}
			}}
		};
	}
};
BiomeProperties biomeProperties[1024];

class Biome{
public:
	BiomeType type;
	int id;
	BiomeProperties& GetProperties(){
		return biomeProperties[id];
	}
};

}

namespace IntServer::Biomes{

int biomeCount = 0;
Biome OCEAN;
Biome PLAINS;

void RegisterBiome( Biome &biome , BiomeType biomeType , BiomeProperties biomeProperties ){
	biomeCount += 1;
	const int biomeId = biomeCount;
	biome = Biome{ type: biomeType , id: biomeId };
	biomeProperties.id = biomeId;
	IntServer::biomeProperties[biomeId] = biomeProperties;
}

void RegisterBiomes(){
	RegisterBiome(OCEAN,BiomeType::OCEAN,BiomeProperties{
		name: "ocean",
		precipitation: "rain",
		depth: -1.0f,
		temperature: 0.5f,
		scale: 0.1f,
		downfall: 0.5f,
		category: "ocean",
		effect_sky_color: 8103167,
		effect_water_fog_color: 329011,
		effect_fog_color: 12638463,
		effect_water_color: 4159204
	});
	RegisterBiome(PLAINS,BiomeType::PLAINS,BiomeProperties{
		name: "plains",
		precipitation: "rain",
		depth: 0.125f,
		temperature: 0.8f,
		scale: 0.05f,
		downfall: 0.4f,
		category: "plains",
		effect_sky_color: 7907327,
	    effect_water_fog_color: 329011,
	    effect_fog_color: 12638463,
	    effect_water_color: 4159204,
	});
}

}
