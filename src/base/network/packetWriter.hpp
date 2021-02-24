#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "base/common.hpp"

namespace IntServer::Network{

class PacketWriter{
public:
	static constexpr int MAX_LENGTH = 2097151+10;	// 内存使用量可优化

	byte bytes[MAX_LENGTH]; int p; int clientFd;

	inline void SetClientFd( int x ){
		clientFd = x;
	}
	inline void WriteByte( byte x ){
		bytes[p++] = x;
	}
	void Init( int packetId ){
		p = 0;
		WriteByte(packetId);
	}

	void Send( bool lengthPrefixed = true ){
		if( __builtin_expect(lengthPrefixed,true) ){
			static byte t_bytes[MAX_LENGTH];
			int t_len = p;
			memcpy(t_bytes,bytes,t_len);
			p = 0;
			WriteVarInt(t_len);
			memcpy(bytes+p,t_bytes,t_len);
			send(clientFd,bytes,p+t_len,0);
		}else{
			send(clientFd,bytes,p,0);
		}

		// std::cout << "[SEND PACK]";
		// for( int i = 0 ; i < p+t_len ; ++i )
		// 	std::cout << std::bitset<8>(bytes[i]);
		// std::cout << std::endl;

	}

	void WriteBoolean( bool value ){
		WriteByte((byte)value);
	}
	void WriteVarInt( int value ){
		do{
			byte t = (byte)(value&0x7F);
			value >>= 7;
			if(value)
				t |= 0x80;
			WriteByte(t);
		}while(value);
	}
	void WriteString( string s ){
		int len = s.length();
		WriteVarInt(len);
		for( auto iter = s.begin() ; iter != s.end() ; iter = std::next(iter) ){
			WriteByte(*iter);
		}
	}
	void WriteLong( ll x ){
		for( int i = 0 ; i < 8 ; ++i ){
			WriteByte((x>>(7-i)*8)&0xFF);
		}
	}
	void WriteUnsignedLong( ull x ){
		for( int i = 0 ; i < 8 ; ++i ){
			WriteByte((x>>(7-i)*8)&0xFF);
		}
	}
	void WriteUUID( UUID x ){	// current: uuid is a 'unsigned long long'
		WriteUnsignedLong(0ULL);
		WriteUnsignedLong(x);
	}
	void WriteInt( int x ){
		WriteByte(x>>3&0xFF);
		WriteByte(x>>2&0xFF);
		WriteByte(x>>1&0xFF);
		WriteByte(x&0xFF);
	}
	void WriteDouble( double x ){
		// 假设操作系统使用小端序
		const char* addr = (char*)(&x);
		WriteByte(*(addr+7));
		WriteByte(*(addr+6));
		WriteByte(*(addr+5));
		WriteByte(*(addr+4));
		WriteByte(*(addr+3));
		WriteByte(*(addr+2));
		WriteByte(*(addr+1));
		WriteByte(*(addr));
	}
	void WriteFloat( float x ){
		// 假设操作系统使用小端序
		const char* addr = (char*)(&x);
		WriteByte(*(addr+3));
		WriteByte(*(addr+2));
		WriteByte(*(addr+1));
		WriteByte(*(addr));
	}
};

}
