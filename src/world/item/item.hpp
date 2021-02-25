#pragma once

namespace IntServer{

enum class ItemType : int{
	GRASS_BLOCK,
	STONE
};

class ItemProperties{
public:
	ItemType type;
	string name;
};
ItemProperties itemProperties[16384];

class Item{
public:
	ItemType type;
	ItemProperties& GetProperties(){
		return itemProperties[static_cast<int>(type)];
	}
};

}

namespace IntServer::Items{

int itemCount = 0;
Item GRASS_BLOCK;
Item STONE;

void RegisterItem( Item &item , ItemType itemType , ItemProperties itemProperties ){
	++itemCount;
	item = Item{ type: itemType };
	itemProperties.type = itemType;
	IntServer::itemProperties[static_cast<int>(itemType)] = itemProperties;
}

void RegisterDefaultItems(){
	RegisterItem(GRASS_BLOCK,ItemType::GRASS_BLOCK,{
		name: "grass_block"
	});

	RegisterItem(STONE,ItemType::STONE,{
		name: "stone"
	});
}

}
