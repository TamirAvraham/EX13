#pragma once
#include "Server.h"
#include "Helper.h"
#include <thread>
#include <string>
#include <functional>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
class MessgaeServer:public Server
{
	using user = std::pair<std::string, SOCKET>;
	using convo = std::pair<std::string, std::fstream>;
public:
	MessgaeServer();
	void init();
private:
	std::vector<user> _users;
	std::map< std::string, std::fstream > _convos;
	std::queue<std::string> _msgs;

	void clientHandler(SOCKET) override;
	void sendAcceptClient(SOCKET)const;

	std::string getConnectedUsers();
	

};

