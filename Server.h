#pragma once

#include <WinSock2.h>
#include <Windows.h>


class Server
{
public:
	Server();
	~Server();
	void serve(int port);

protected:

	void acceptClient();
	virtual void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};

