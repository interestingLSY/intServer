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

namespace IntServer::Network{

class ConnectionEndException : public std::exception{
public:
	const char* what(){
		return "Connection ends";
	}
};

}

#include "base/network/packetReader.hpp"
#include "base/network/packetWriter.hpp"
#include "base/network/clientHandler.hpp"

namespace IntServer::Network{

int sockFd;
void Bind( int port ){
	sockFd = socket(AF_INET,SOCK_STREAM,0);
	Assert( sockFd >= 0 );

	sockaddr_in addrServer;
	memset(&addrServer,0,sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

	{
		int opt = 1;
		setsockopt(sockFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	}

	int bindResult = bind(sockFd,(struct sockaddr *)&addrServer,sizeof(struct sockaddr_in));
	Assert( bindResult == 0 );
	int listenResult = listen(sockFd,10);
	Assert( listenResult == 0 );
}

void Listen(){
	sockaddr_in addrClient;
	unsigned int addrClientLen = 0;
	usleep(10*1000);
	int clientFd = accept(sockFd,(struct sockaddr *)&addrClient,&addrClientLen);

	if( clientFd > 0 ){
		Debug("Accepted client",clientFd,inet_ntoa(addrClient.sin_addr));
		std::thread clientHandlerThread([clientFd,&addrClient](){
			ClientHandler clientHandler(clientFd,&addrClient);
			clientHandler.Listen();
		});
		clientHandlerThread.detach();
	}else{
		Error("clientFd <= 0!","clientFd =",clientFd,"Errno =",errno,strerror(errno));
		close(clientFd);
	}

	Listen();
}

void StopTCPServer(){
	close(sockFd);
}

void StartTCPServer( int port ){
	Bind(port);
	atexit(StopTCPServer);
	Listen();
}

}
