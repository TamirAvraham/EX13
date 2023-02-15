#pragma once

#include "Server.h"
#include "Helper.h"
#include <thread>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <mutex>
#include <condition_variable>
class MessgaeServer:public Server
{
	using user = std::pair<std::string, SOCKET>;
public:
	MessgaeServer();
	void init();
private:
	std::map<std::string, std::string> _messages;
	std::list<std::string> _userNames;
	std::string _key;
	std::list<std::thread> _threads;
	std::mutex _mtx1;
	std::mutex _mtx2;
	std::condition_variable _cv;

	void clientHandler(SOCKET) override;
	void handleMessage();

	std::string connectedUsers();
	void addUser(std::string name);
	void addMessage(std::string message);
	std::string getAllMessages();
	void deleteName(std::string name);


};

