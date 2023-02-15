#pragma warning(disable : 4996)
#include "Helper.h"
#include <fstream>
#include <iomanip>
#include <sstream>

//check if file exist
bool Helper::isFileExist(std::string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(char* data)
{
	std::string msg = getPartFromSocket(data, 0, 3);
	if (msg == "")
		return 0;

	int res = std::stoi(msg);
	return  res;
}


void Helper::send_update_message_to_client(SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users)
{
	//TRACE("all users: %s\n", all_users.c_str())
	const std::string code = std::to_string(MT_SERVER_UPDATE);
	const std::string current_file_size = getPaddedNumber(file_content.size(), 5);
	const std::string username_size = getPaddedNumber(second_username.size(), 2);
	const std::string all_users_size = getPaddedNumber(all_users.size(), 5);
	const std::string res = code + current_file_size + file_content + username_size + second_username + all_users_size + all_users;
	//TRACE("message: %s\n", res.c_str());
	sendData(sc, res);
}

// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(char* data, int begin, int size)
{
	std::string s = getPartFromSocket(data, begin, size);
	return std::stoi(s);
}

// return string after padding zeros if necessary
std::string Helper::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();

}

char* Helper::getDataFromSocket(SOCKET sc)
{
	char data[100] = { 0 };
	int res = recv(sc, data, 100, 0);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	char* m = new char[strlen(data) + 1];
	m[strlen(data)] = NULL;
	strncpy(m, data, strlen(data));
	return m;
}

std::string Helper::getPartFromSocket(char* data, int begin, int size)
{
	std::string result(data);
	return result.substr(begin, size);
}

// send data to socket
// this is private function
void Helper::sendData(SOCKET sc, std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}
