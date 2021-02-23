#pragma once

namespace IntServer{

template<typename T>
struct V2{
	T x,z;
};
template<typename T>
inline bool operator<( const V2<T> &a , const V2<T> &b ){
	return a.x != b.x ? a.x < b.x : a.z < b.z;
}
template<typename T>
std::ostream& operator<<( std::ostream &oStream , const V2<T> v2 ){
	oStream << '(' << v2.x << ' ' << v2.z << ')';
	return oStream;
}
#define V2d V2<double>
#define V2i V2<int>


template<typename T>
struct V3{
	T x,y,z;
};
template<typename T>
inline bool operator<( const V3<T> &a , const V3<T> &b ){
	return a.x != b.x ? a.x < b.x :
			a.y != b.y ? a.y < b.y : a.z < b.z;
}
template<typename T>
std::ostream& operator<<( std::ostream &oStream , const V3<T> v3 ){
	oStream << '(' << v3.x << ' ' << v3.y << ' ' << v3.z << ')';
	return oStream;
}
#define V3d V3<double>
#define V3i V3<int>

}
