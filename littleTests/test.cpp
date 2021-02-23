#include <iostream>
// #include "../src/3rdparty/cpp-nbt/nbt/nbt.hpp"
#include <typeinfo>
#include <map>
#include <vector>

using namespace std;

enum class TagType : int{
	TAG_End = 0,
	TAG_Byte = 1,
	TAG_Short = 2,
	TAG_Int = 3,
	TAG_Long = 4,
	TAG_Float = 5,
	TAG_Double = 6,
	TAG_Byte_Array = 7,
	TAG_String = 8,
	TAG_List = 9,
	TAG_Compound = 10,
	TAG_Int_Array = 11,
	TAG_Long_Array = 12
};

typedef unsigned char byte;
typedef long long ll;

// class TagReader{
// public:
// 	static constexpr int MAX_SIZE = 131072;
// 	byte bytes[MAX_SIZE];
// 	void Read
// };

template<TagType tagType, typename TypeName>
class Tag{
public:
	TypeName val;
};




int main(){

	vector<Base> v;
	E1 e1; E2(e2);
	v.push_back(e1);
	v.push_back(e2);
	for( auto x : v ){
		cout << x.GetType() << endl;
	}

	return 0;
}
