#pragma once
#include <vector>
#include "../OverallClass/NetworkStrData.h"
#include "../OverallClass/Hand.h"
#include "../OverallClass/ConfigurationFile.h"
#include "Algorithm.h"
#include "NewFileSave.h"
#include "TradeMacd.h"

#define IFCelLue04		4	//单
#define IFCelLue05		5	//单	//BOLL+MACD+SAR指标
#define IFCelLue06		6	//单	//MACD指标 
#define IFCelLue07		7	//单	//MACD长线判断多与空指标 
#define IFCelLue08		8	//单	//MACD长线判断多与空指标 7的反向多做空  空做多
#define IFCelLue09		9	//单	//MACD长线判断多与空指标 7的反向多做空  空做多
#define CelLue			IFCelLue09

class MainTrade
{
public:
	MainTrade();
	~MainTrade();
public:
	void Push(STR_USDT& buff);
private:
	void RunTrade(std::vector<STR_USDT>& ve, STR_USDT& NewUSD);
private:
	void JsonReadFileValue();
	void Pretreatment(std::vector<STR_USDT>& ve);				//预处理
	void MoveData(std::vector<STR_USDT>& ve, STR_USDT& base);
private:
	std::vector<STR_USDT>m_Long;
	STR_MacdValue m_MacdValue;
private:									//
	TradeMacd* m_Trade;
};