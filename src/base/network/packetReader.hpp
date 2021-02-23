#pragma once

#include <bitset>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "base/common.hpp"

namespace IntServer::Network{

class PacketReader{
public:
	static constexpr int MAX_LENGTH = 2097151+10;	// 内存使用量可优化

	byte bytes[MAX_LENGTH]; int p; int recvLen;
	int clientFd;

	inline void SetClientFd( int x ){
		clientFd = x;
	}

	inline byte ReadByte(){
		Assert( p < recvLen );
		return bytes[p++];
	}
	bool ReadBool(){
		return !!ReadByte();
	}
	ushort ReadUnsignedSort(){
		ushort result = 0;
		result |= ushort(ReadByte()) << 8;
		result |= ReadByte();
		return result;
	}
	int ReadVarInt(){
		int result = 0;
		int numRead = 0;
		byte t;
		do{
			t = ReadByte();
			result |= (t & 0x7F) << 7*numRead;
			++numRead;
			Assert( numRead <= 5 );
		}while( t & 0x80 );
		return result;
	}
	ll ReadVarLong(){
		ll result = 0;
		int numRead = 0;
		byte t;
		do{
			t = ReadByte();
			result |= (t & 0x7F) << 7*numRead;
			++numRead;
			Assert( numRead <= 10 );
		}while( t & 0x80 );
		return result;
	}
	ll ReadLong(){
		ll result = 0;
		for( int i = 0 ; i < 8 ; ++i )
			result = result | (((ll)ReadByte()) << (i*8));
		return result;
	}
	void ReadString( string* s ){
		if( s != nullptr ) s->clear();
		int len = ReadVarInt();
		for( int i = 0 ; i < len ; ++i ){
			byte c = ReadByte();
			if( s != nullptr ) s->push_back(c);
		}
	}

	int Recv(){
		p = 0;
		recvLen = recv(clientFd,bytes,MAX_LENGTH,0);
		// Assert( recvLen >= 0 );

		// std::cout << "[RECV PACK]";
		// for( int i = 0 ; i < recvLen ; ++i )
		// 	std::cout << std::bitset<8>(bytes[i]) << ' ';
		// std::cout << std::endl;

		if( recvLen > 0 ){
			if( bytes[0] == 0xFE ){	 // legacy "PING" request
				bytes[0] = 0x7F;
			}else{		// take off the "length" field
				ReadVarInt();
			}
		}elif( recvLen <= 0 ){
			if( recvLen == -1 and errno != 22 )
				Error("Unknown errno:",errno);
			throw ConnectionEndException();
		}
		return recvLen;
	}

};

}
