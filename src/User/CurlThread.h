#pragma once
#include <vector>
#include <string>
#include <boost/signals2.hpp>
#include "../communication/QCurl.h"
#include "../OverallClass/Hand.h"
#include "../Timer/TimerCount.h"
class CurlThread
{
public:
	CurlThread(QCulReadClass* QCulReadClass, std::string USDTName, std::string H, long long Ms);
	void set(QCulReadClass* QCulReadClass);
	~CurlThread();
public:
	boost::signals2::signal<void(STR_BaseKlines)>SignalsData;
	boost::signals2::signal<void(STR_BTC_Price)>SignalsPrice;
public:
	void run();
	void EndThread();
	void klines();
	void getServerTimer();
	double getPrice();
private:
	double getPrivatePrice();
	void NewIni();
	void ReadCurl();
	void ReadCurl(unsigned long long Timer);
	void Price();
	void JsonBase(std::string& buff);
	void GroupData(STR_BTC_Price& buff);
	void GroupData(STR_BaseKlines& buff);
private:
	std::string m_USDTName;
	std::string m_String_H;
	long long m_Ms;
	long long UTC;
	long long m_ServerTimer;
	bool IsIni;
	double m_Price;
	QCulReadClass* m_Curl;
	Jump::TimerCount m_TimerCount;
};