#pragma once
#include <vector>
#include "../OverallClass/NetworkStrData.h"
#include "../OverallClass/Hand.h"
#include "../OverallClass/ConfigurationFile.h"
#include "Algorithm.h"
#include "NewFileSave.h"
#include "TradeMacd.h"

#define IFCelLue04		4	//��
#define IFCelLue05		5	//��	//BOLL+MACD+SARָ��
#define IFCelLue06		6	//��	//MACDָ�� 
#define IFCelLue07		7	//��	//MACD�����ж϶����ָ�� 
#define IFCelLue08		8	//��	//MACD�����ж϶����ָ�� 7�ķ��������  ������
#define IFCelLue09		9	//��	//MACD�����ж϶����ָ�� 7�ķ��������  ������
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
	void Pretreatment(std::vector<STR_USDT>& ve);				//Ԥ����
	void MoveData(std::vector<STR_USDT>& ve, STR_USDT& base);
private:
	std::vector<STR_USDT>m_Long;
	STR_MacdValue m_MacdValue;
private:									//
	TradeMacd* m_Trade;
};