#pragma once

#include "base/common.hpp"

namespace IntServer{

enum class BlockType : int{
	GRASS_BLOCK,
	STONE
};

class Block{
public:
	BlockType type;
	string idener;
};

}


namespace IntServer::Blocks{

#define RegisterBlock(name,...) \
	Block name __VA_ARGS__

RegisterBlock(GRASS_BLOCK,{
	type: BlockType::GRASS_BLOCK,
	idener: "grass_block"
});

RegisterBlock(STONE,{
	type: BlockType::STONE,
	idener: "stone"
});

}
