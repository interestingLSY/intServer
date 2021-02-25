#pragma once

#include "base/common.hpp"
#include "itemStack.hpp"

namespace IntServer{

template<size_t SIZE>
class ItemStackGroup{
public:
	ItemStack itemStacks[SIZE];
};

};
