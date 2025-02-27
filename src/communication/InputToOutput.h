#pragma once
#include <boost/signals2.hpp>
#include <mutex>
#include "BoostTCP.h"
#include "../OverallClass/SocketType.h"
class InputToOutput : public Jump::TCP
{
public:
	InputToOutput(std::string IP = "", short Port = 0);
	~InputToOutput();
	bool IsOpen();
public:
	int GroupData(UI_Type Type, char* buff, int len);		//组包类型
	int GroupData(UI_Type Type, void* buff, int len);		//组包类型
public://signals信号发出
private:
	void OutThread();
	void ReadSocketData(void* buff);
private:
	std::mutex m_Mutex;
	bool m_IsThread;
};