#pragma once
#include "Server.h"
#include "Helper.h"
#include <thread>
#include <string>
#include <functional>
#include <queue>
#include <list>
class MessgaeServer:public Server
{
	using user = std::pair<std::string, SOCKET>;
public:
	MessgaeServer();
	void init();
private:
	std::list<user> _users;
	std::queue<std::string> _msgs;

	void clientHandler(SOCKET) override;
	void sendAcceptClient(SOCKET)const;

	std::string getConnectedUsers();

};

