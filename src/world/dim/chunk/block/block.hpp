#pragma once

#include "base/common.hpp"

namespace IntServer{

enum class BlockType : int{
	GRASS_BLOCK,
	STONE
};

class BlockProperties{
public:
	BlockType type;
	string name;
};
BlockProperties blockProperties[16384];

class Block{
public:
	BlockType type;
	BlockProperties& GetProperties(){
		return blockProperties[static_cast<int>(type)];
	}
};

}


namespace IntServer::Blocks{

int blockCount = 0;
Block GRASS_BLOCK;
Block STONE;

void RegisterBlock( Block &block , BlockType blockType , BlockProperties blockProperties ){
	++blockCount;
	block = Block{ type: blockType };
	blockProperties.type = blockType;
	IntServer::blockProperties[static_cast<int>(blockType)] = blockProperties;
}

void RegisterDefaultBlocks(){
	RegisterBlock(GRASS_BLOCK,BlockType::GRASS_BLOCK,{
		type: BlockType::GRASS_BLOCK,
		name: "grass_block"
	});

	RegisterBlock(STONE,BlockType::STONE,{
		type: BlockType::STONE,
		name: "stone"
	});
}

}
