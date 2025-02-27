#include "Overall.h"
#include "../communication/Json.h"
InputToOutput m_InputToOutput(
	Jump::JsonRead("Ini/Socket.json", "IP"),
	(int)std::atoll(Jump::JsonRead("Ini/Socket.json", "Port").c_str()));		//UDP通讯
QCulReadClass m_QCulReadClass;								//curl初始化
CurlThread m_CurlThread(&m_QCulReadClass,					//curl获取数据初始化
	Jump::JsonRead("Ini/数据相关配置.json", "虚拟币名字"),
	Jump::JsonRead("Ini/数据相关配置.json", "长线"),
	(int)std::atoll(Jump::JsonRead("Ini/数据相关配置.json", "长期网络上获取数据时间差").c_str()));
Jump::TimerCount m_TimerCount;

InputToOutput* OverallSocket()
{
	return &m_InputToOutput;
}

QCulReadClass* OverallCurl()
{
	return &m_QCulReadClass;
}

CurlThread* OverallCurlThread()
{
	return &m_CurlThread;
}

Jump::TimerCount* OverallTimer()
{
	return &m_TimerCount;
}
