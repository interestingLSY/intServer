#pragma once

#include <cstring>

#include "base/common.hpp"

namespace IntServer{

enum class BlockType : int{
	GRASS_BLOCK,
	STONE
};

class Block{
public:
	BlockType type;
	string name;
};

}


namespace IntServer::Blocks{

Block GRASS_BLOCK = Block{
	type: BlockType::GRASS_BLOCK,
	name: "grass_block"
};

Block STONE = Block{
	type: BlockType::STONE,
	name: "stone"
};

}
