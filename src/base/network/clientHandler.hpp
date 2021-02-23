#pragma once

#include <cstdlib>
#include <vector>
#include <thread>
#include <exception>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "base/common.hpp"
#include "base/io/log.hpp"
#include "base/network/packetReader.hpp"
#include "base/network/packetWriter.hpp"

#include "player/player.hpp"
#include "world/world.hpp"
// #include "nbt_tags.h"

namespace IntServer::Network{

class ClientHandler{
public:
	sockaddr_in *addrClient;
	int clientFd;
	int stage;
	PacketReader packetReader;
	PacketWriter packetWriter;

	Player player;

	~ClientHandler(){
		close(clientFd);
		if( player.uuid != 0 )	// if player.uuid is generated
			Worlds::RemovePlayerFromAllWorlds(player.uuid);
	}
	ClientHandler( int _clientFd , sockaddr_in *_addrClient ){
		clientFd = _clientFd;
		addrClient = _addrClient;
		stage = 1;
		packetReader.SetClientFd(clientFd);
		packetWriter.SetClientFd(clientFd);
		player.uuid = 0;
	}

	void Listen(){
		while(1){
			try{
				int recvLen = packetReader.Recv();
				int packetId = packetReader.ReadVarInt();
				Debug("Accept packet from",inet_ntoa(addrClient->sin_addr),"Packet id:",packetId,"recvLen",recvLen,"stage",stage);

				if( stage == 1 ){
					if( packetId == 0x00 ) HandlePacketStage1Id0x00();
					elif( packetId == 0x01 ) HandlePacketStage1Id0x01();
					elif( packetId == 0x7F ) HandlePacketStage1Id0x7F();
				}elif( stage == 2 ){
					if( packetId == 0x00 ) HandlePacketStage2Id0x00();
				}elif( stage == 3 ){

				}
			}catch( ConnectionEndException &e ){
				break;
			}
		}
	}

	// followed by some bullshit

	// Stage 1: Status
	#include "packetHandlers/handlePacketStage1Id0x00.hpp"
	#include "packetHandlers/handlePacketStage1Id0x01.hpp"
	#include "packetHandlers/handlePacketStage1Id0x7F.hpp"

	// Stage 2: Login
	#include "packetHandlers/handlePacketStage2Id0x00.hpp"

	// Stage 3: Play

	void SendPacket0x32_PlayerInfo_AddPlayer( UUID uuid , string playerName , Gamemode gamemode , int ping ){
		packetWriter.Init(0x32);
		packetWriter.WriteVarInt(0);
		packetWriter.WriteVarInt(1);
		packetWriter.WriteUUID(uuid);
		packetWriter.WriteString(playerName);
		packetWriter.WriteVarInt(0);
		packetWriter.WriteVarInt(static_cast<int>(gamemode));
		packetWriter.WriteVarInt(ping);
		packetWriter.WriteBoolean(false);
		packetWriter.Send();
	}
	void SendPacket0x34_PlayerPositionAndLook( V3d position , float yaw = 0 , float pitch = 0 ){
		packetWriter.Init(0x34);
		packetWriter.WriteDouble(position.x);
		packetWriter.WriteDouble(position.y);
		packetWriter.WriteDouble(position.z);
		packetWriter.WriteFloat(yaw);
		packetWriter.WriteFloat(pitch);
		packetWriter.WriteByte(0);
		packetWriter.WriteVarInt(1);
		packetWriter.Send();
	}
};

}
