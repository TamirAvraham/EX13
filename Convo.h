#pragma once
#include <string>
#include <queue>
#include <fstream>
#include <condition_variable>
#include <mutex>
class Convo
{
public:
	Convo(std::string name);
	void insertMsg(std::string);
	std::string getLatest();
	std::string getAllMsgs();
private:
	void writezToFile();
	std::string _name;
	std::queue<std::string> _msgs;
	std::ofstream _file;
	std::condition_variable _fileLock;
	std::mutex _qLock;
};

