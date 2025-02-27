#include "CurlThread.h"
#include <thread>
#include <json/json.h>
#include <boost/algorithm/string.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#include "../OverallClass/Overall.h"
#define CurlSize 500
CurlThread::CurlThread(QCulReadClass* QCulReadClass, std::string USDTName, std::string H, long long Ms)
{
	this->m_USDTName = USDTName;
	this->UTC = 0;
	this->m_Ms = Ms;
	this->m_String_H = H;
	m_Curl = QCulReadClass;
	IsIni = true;
	run();
}

void CurlThread::set(QCulReadClass* QCulReadClass)
{
	m_Curl = QCulReadClass;
}

CurlThread::~CurlThread()
{

}

void CurlThread::EndThread()
{

}

void CurlThread::NewIni()
{
	klines();
}

void CurlThread::run()
{
	std::thread t1(&CurlThread::NewIni, this);
	t1.detach();
}

void CurlThread::klines()
{
	while (1)
	{
		if (IsIni)
		{
			unsigned long long timestamp = m_TimerCount.getTimerUTC();
			this->ReadCurl();
		}
		else
		{
			getServerTimer();
		}
		m_Price = getPrivatePrice();
		m_TimerCount.Sleep(1000);
	}
}

void CurlThread::getServerTimer()
{
	std::string Buff;
	std::string Curl = std::string(期货API) + std::string(服务器时间);
	m_Curl->Get(Buff, Curl);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(Buff, root, false))
	{
		//获取键值
		long long age = std::atoll(root["serverTime"].asString().c_str());
		if (age > this->UTC + (this->m_Ms + 1000))
		{
			this->ReadCurl(age);
		}
	}
}

double CurlThread::getPrice()
{
	return m_Price;
}

double CurlThread::getPrivatePrice()
{
	std::string Buff;
	std::string Curl = std::string(期货API) + std::string(期货最新价) + this->m_USDTName;
	m_Curl->Get(Buff, Curl);
	Json::Reader reader;
	Json::Value root;
	double age = 0;
	if (reader.parse(Buff, root, false))
	{
		// 获取键值
		age = std::stod(root["price"].asString().c_str());
	}
	return age;
}

void CurlThread::ReadCurl()
{
	std::string Buff;
	std::string Curl = std::string(期货API) + std::string(期货K线) + this->m_USDTName + "&interval=" + this->m_String_H + "&limit=" + std::to_string(CurlSize);
	m_Curl->Get(Buff, Curl);
	//JsonBase(Buff);
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(Buff, root);
	for (int i = 0; i < (int)root.size() - 1; i++)
	{
		if (root[i].size() > 5)
		{
			STR_BaseKlines BaseKlines;
			BaseKlines.Time = root[i][0].asUInt64();			 //时间
			BaseKlines.open = std::stod(root[i][1].asString());	 //开盘
			BaseKlines.high = std::stod(root[i][2].asString());	 //最高
			BaseKlines.low = std::stod(root[i][3].asString());	 //最低
			BaseKlines.close = std::stod(root[i][4].asString()); //收盘
			if (BaseKlines.Time != this->UTC)
			{
				this->UTC = BaseKlines.Time;
				if (i != CurlSize - 1)
					GroupData(BaseKlines);
				IsIni = false;
				OverallTimer()->Sleep(5);
			}
		}
	}
	if (root.size() != -1)
	{
		int Index = root.size() - 1;
		this->UTC = root[Index][0].asUInt64();			 //时间
	}
}

void CurlThread::JsonBase(std::string& buff)
{
	std::string string = buff;
	boost::erase_all(string, std::string(1, '\"'));
	boost::erase_all(string, std::string(1, ']"'));
	std::vector<std::string> result;
	boost::split(result, string, boost::is_any_of("["));

	STR_BaseKlines Base;
	std::vector<std::string>Value;
	for (int i = 2; i < result.size() - 1; i++)
	{
		boost::split(Value, result[i], boost::is_any_of(","));
		Base.Time = std::stoll(Value[0]);				//时间
		Base.open = std::stod(Value[1]);				//开盘
		Base.high = std::stod(Value[2]);				//最高
		Base.low = std::stod(Value[3]);					//最低
		Base.close = std::stod(Value[4]);				//收盘
		//if (Base.Time != this->UTC)
		//{
		//	if (i != CurlSize - 1)
		//		GroupData(Base);
		//	OverallTimer()->Sleep(5);
		//}
	}
	IsIni = false;
	boost::split(Value, result[result.size() - 1], boost::is_any_of(","));
	this->UTC = std::stoll(Value[0]);				//时间
}

void CurlThread::ReadCurl(unsigned long long Timer)
{
	std::string Buff;
	std::string Curl = std::string(期货API) + std::string(期货K线) + this->m_USDTName + "&interval=" + this->m_String_H + "&limit=" + std::to_string(2);
	m_Curl->Get(Buff, Curl);
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(Buff, root);
	for (int i = 0; i < (int)root.size(); i++)
	{
		if (root[i].size() > 5)
		{
			STR_BaseKlines BaseKlines;
			int Index = root.size() - 2;
			if ((this->UTC + this->m_Ms) == root[Index + 1][0].asUInt64())
			{
				BaseKlines.Time = root[Index][0].asUInt64();			 //时间
				BaseKlines.open = std::stod(root[Index][1].asString());	 //开盘
				BaseKlines.high = std::stod(root[Index][2].asString());	 //最高
				BaseKlines.low = std::stod(root[Index][3].asString());	 //最低
				BaseKlines.close = std::stod(root[Index][4].asString()); //收盘
				this->UTC = root[Index + 1][0].asUInt64();
				GroupData(BaseKlines);
			}
			else
				break;
		}
	}
}

void CurlThread::Price()
{
	std::string Buff;
	std::string Curl = std::string(期货API) + std::string(期货最新价) + this->m_USDTName;
	m_Curl->Get(Buff, Curl);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(Buff, root, false))
	{
		// 获取键值
		STR_BTC_Price STRPrice;
		STRPrice.Price = std::stod(root["price"].asString().c_str());
		GroupData(STRPrice);
	}
}

void CurlThread::GroupData(STR_BTC_Price& buff)
{
	SignalsPrice(buff);
}

void CurlThread::GroupData(STR_BaseKlines& buff)
{
	SignalsData(buff);
}