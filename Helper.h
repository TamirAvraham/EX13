#pragma once

#include <vector>
#include <string>
#include <map>
#include <WinSock2.h>


enum MessageType : byte
{
	MT_CLIENT_LOG_IN = 200,
	MT_CLIENT_UPDATE = 204,
	MT_CLIENT_FINISH = 207,
	MT_CLIENT_EXIT = 208,
	MT_SERVER_UPDATE = 101,
};


class Helper
{
public:
	static bool isFileExist(std::string fileName);
	static int getMessageTypeCode(char* data);
	static int getIntPartFromSocket(char* data, int begin, int size);
	static void sendData(SOCKET sc, std::string message);
	static void send_update_message_to_client(SOCKET sc, const std::string& file_content, const std::string& second_username, const std::string& all_users);
	static std::string getPaddedNumber(int num, int digits);
	static char* getDataFromSocket(SOCKET sc);
	static std::string getPartFromSocket(char* data, int begin, int size);


private:
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum);
	static std::string getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags);

};


#ifdef _DEBUG // vs add this define in debug mode
#include <stdio.h>
// Q: why do we need traces ?
// A: traces are a nice and easy way to detect bugs without even debugging
// or to understand what happened in case we miss the bug in the first time
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
// for convenient reasons we did the traces in stdout
// at general we would do this in the error stream like that
// #define TRACE(msg, ...) fprintf(stderr, msg "\n", __VA_ARGS__);

#else // we want nothing to be printed in release version
#define TRACE(msg, ...) printf(msg "\n", __VA_ARGS__);
#define TRACE(msg, ...) // do nothing
#endif