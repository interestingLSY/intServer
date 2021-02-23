#pragma once

#include "base/common.hpp"

#include "block/block.hpp"

namespace IntServer{

class Chunk{
public:
	Block blockMap[16][256][16];
	Block& GetBlock( V3i blockPos , bool isRelativePos ){
		return isRelativePos ?
				blockMap[blockPos.x&15][blockPos.y][blockPos.z&15] :
				blockMap[blockPos.x][blockPos.y][blockPos.z];
	}
};

V2i UnderWhichChunkCoor( V3i blockPos ){
	return V2i{
		int( (double)blockPos.x / 16 + 1e-5 ),
		int( (double)blockPos.z / 16 + 1e-5 )
	};
}

}
