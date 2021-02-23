#pragma once

template<typename T>
class BaseTag{
public:
	T val;

};

template<typename T>
class TagSingleNumber{
public:

};

typedef Tag<TagType::TAG_End,			bool		> TagEnd;
typedef Tag<TagType::TAG_Byte,			unsigned char> TagByte;
typedef Tag<TagType::TAG_Short,			short		> TagShort;
typedef Tag<TagType::TAG_Int,			int			> TagInt;
typedef Tag<TagType::TAG_Long,			ll			> TagLong;
typedef Tag<TagType::TAG_Float, 		float		> TagFloat;
typedef Tag<TagType::TAG_Double,		double		> TagDouble;
typedef Tag<TagType::TAG_Byte_Array,	vector<unsigned char> > TagByteArray;
typedef Tag<TagType::TAG_String,		string		> TagString;
typedef Tag<TagType::TAG_List,			vector<Tag>	> TagList;
typedef Tag<TagType::TAG_Compound,		vector<Tag>	> TagCompound;
typedef Tag<TagType::TAG_Int_Array,		vector<int>	> TagIntAray;
typedef Tag<TagType::TAG_Long_Array,	vector<ll>	> TagLongArray;
