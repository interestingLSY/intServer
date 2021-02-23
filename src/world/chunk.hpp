#pragma once

#include "base/common.hpp"
#include "block/block.hpp"

namespace IntServer{

class IChunk{
protected:
	Block blockMap[16][256][16];
public:
	Block& GetBlockFromRelPos_W( V3i blockPos ){
		return blockMap[blockPos.x][blockPos.y][blockPos.z];
	}
	Block GetBlockFromRelPos( V3i blockPos ){
		return GetBlockFromRelPos_W(blockPos);
	}
	Block& GetBlockFromAbsPos_W( V3i blockPos ){
		return blockMap[blockPos.x&15][blockPos.y][blockPos.z&15];
	}
	Block GetBlockFromAbsPos( V3i blockPos ){
		return GetBlockFromAbsPos_W(blockPos);
	}
};

class Chunk : public IChunk{
public:
	V2i chunkPos;
	Chunk(){}
	Chunk( V2i _chunkPos ){
		chunkPos = _chunkPos;
	}
};

}
