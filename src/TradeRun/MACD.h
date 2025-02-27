#pragma once
//#include "..\..\APP\Chart\qcustomplot.h"
#include <vector>
#include "../OverallClass/NetworkStrData.h"
class MACD
{
public:
	MACD(int optInFastPeriod = 16, int optInSlowPeriod = 30, int optInSignalPeriod = 11); //BTC参数
	~MACD();
public:
	STR_Macd GetValue(std::vector<STR_USDT>& close, int index);
private:
	int m_OptInFastPeriod;
	int m_OptInSlowPeriod;
	int m_OptInSignalPeriod;
};

