#include "MessgaeServer.h"

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
	sendAcceptClient(sock);
	while (true)
	{
		//handle the msg sender
	}
}

void MessgaeServer::sendAcceptClient(SOCKET sock) const
{
	std::string m = Helper::getDataFromSocket(sock);
	int lenName = std::atoi(m.substr(2,3).c_str()), lenMessage = 0;
	// build first update message and save user
	std::string name = m.substr( 5, lenName);
	

}
