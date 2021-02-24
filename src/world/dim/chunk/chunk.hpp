#pragma once

#include "base/common.hpp"

#include "block/block.hpp"
#include "biome/biome.hpp"

namespace IntServer{

class Chunk{
public:
	Block blockMap[16][256][16];
	Biome biomeMap[16][256][16];

	// 相对坐标和绝对坐标都可以接受
	// Both relative-position and absolute-position is acceptable
	Block& GetBlock( V3i blockPos ){
		return blockMap[blockPos.x&15][blockPos.y][blockPos.z&15];
	}
	Biome& GetBiome( V3i biomePos ){	// biomePos is
		return biomeMap[biomePos.x&15][biomePos.y][biomePos.z&15];
	}
};

V2i UnderWhichChunkCoor( V3i pos ){
	return V2i{
		int( (double)pos.x / 16 + 1e-5 ),
		int( (double)pos.z / 16 + 1e-5 )
	};
}

}
