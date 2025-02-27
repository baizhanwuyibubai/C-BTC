#pragma once
#include <fstream>
#include "../OverallClass/NetworkStrData.h"
#include "../OverallClass/ConfigurationFile.h"
#include "../OverallClass/SocketType.h"
#include "../OverallClass/Overall.h"
#include "NewFileSave.h"
#include "Algorithm.h"
#define IFCelLue04		4	//单
#define IFCelLue05		5	//单	//BOLL+MACD+SAR指标
#define IFCelLue06		6	//单	//MACD指标 
#define IFCelLue07		7	//单	//MACD长线判断多与空指标 
#define IFCelLue08		8	//单	//MACD长线判断多与空指标 7的反向多做空  空做多
#define IFCelLue09		9	//单	//MACD长线判断多与空指标 7的反向多做空  空做多
#define CelLue			IFCelLue09

class TradeMacd : public Algorithm
{
public:
	TradeMacd(STR_MacdValue& MacdValue);
	~TradeMacd();
public:
	void RunDuoToKong(STR_USDT& NewUSD);
private:
	void RunOpenDuo(STR_USDT& USD);
	void Open(STR_New_Buy& Buy, unsigned char CurrentState);
	void Close(STR_New_Sell& Sell, unsigned char CurrentState);
	double Money(unsigned char CurrentState);
private://向外发送数据
	void SocketOpen(double New_Price, long long Timer, unsigned char CurrentState);
	void SocketClose(double New_Price, long long Timer, double Cash, double BTC_Income, unsigned char CurrentState);
private:
	unsigned char m_CurrentState;			//做多种或做空中
	bool m_TradeTimer;						//判断是否开仓
	double m_UserMoney;
	STR_BTC_New_Buy_Sell m_New_BuySell;
	STR_MacdValue m_MacdValue;
};