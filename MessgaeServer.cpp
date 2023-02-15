#include "MessgaeServer.h"
#include <iostream>
void MessgaeServer::init()
{
	std::thread accepter([this]() {
		while (true)
		{
			acceptClient();
		}
	});
}



void MessgaeServer::clientHandler(SOCKET sock)
{
	std::string name1;
	try
	{
		std::string name, secondeName, message, fileContent, path;
		char* m = Helper::getDataFromSocket(sock);
		int lenName = Helper::getIntPartFromSocket(m, 3, 2), lenMessage = 0;
		// build first update message and save user
		name = Helper::getPartFromSocket(m, 5, lenName);
		name1 = name;
		addUser(name);
		std::cout << connectedUsers() << std::endl;
		Helper::send_update_message_to_client(sock, "", "", connectedUsers());
		while (true)
		{
			m = Helper::getDataFromSocket(sock);
			lenName = Helper::getIntPartFromSocket(m, 3, 2);
			secondeName = Helper::getPartFromSocket(m, 5, lenName);
			lenMessage = Helper::getIntPartFromSocket(m, 5 + lenName, 5);
			message = Helper::getPartFromSocket(m, 10 + lenName, lenMessage);
			fileContent = "";
			if (name < secondeName)
			{
				path = name + "&" + secondeName + ".txt";
			}
			else
			{
				path = secondeName + "&" + name + ".txt";
			}
			_mtx2.lock();
			_key=path;
			if (message != "")
			{
				std::unique_lock<std::mutex> lock(_mtx1); // lock
				addMessage("&MAGSH_MESSAGE&&Author&" + name + "&DATA&" + message);
				lock.unlock();// unlock
				_cv.notify_one();
			}
			_mtx2.unlock();
			fileContent = getAllMessages();

			Helper::send_update_message_to_client(sock, fileContent, secondeName, connectedUsers());
		}

		// Closing the socket (in the level of the TCP protocol)
		closesocket(sock);
	}
	catch (const std::exception& e)
	{
		closesocket(sock);
		deleteName(name1);
	}

}



void MessgaeServer::handleMessage()
{
	std::ofstream chat;
	while (1)
	{
		std::unique_lock<std::mutex> lock(_mtx1);
		_cv.wait(lock);
		chat.open(_key, std::ofstream::out | std::ofstream::trunc);
		chat.close();
		chat.open(_key);
		chat << getAllMessages();
		chat.close();
		lock.unlock();
	}

}

std::string MessgaeServer::connectedUsers()
{
	std::string userList;
	for (auto const& i : _userNames)
	{
		userList += i;
		userList += "&";
	}

	userList = userList.substr(0, userList.size() - 1);
	return userList;

}

void MessgaeServer::addUser(std::string name)
{
	_userNames.push_back(name);
}

void MessgaeServer::addMessage(std::string message)
{
	if (_messages.find(_key) == _messages.end())
	{
		_messages.insert({ _key, message });//init list for the first time
	}
	else
	{
		_messages[_key] += message;
	}

}

std::string MessgaeServer::getAllMessages()
{
	 return _messages[_key];
}


void MessgaeServer::deleteName(std::string name)
{
}

