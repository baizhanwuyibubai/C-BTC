#pragma once
//#include "..\..\APP\Chart\qcustomplot.h"
#include <vector>
#include "../OverallClass/NetworkStrData.h"
class RSI
{
public:
	RSI(int Short = 16); //BTC参数
	~RSI();
public:
	STR_RSI GetValue(std::vector<STR_USDT>& close, int index);
private:
	int m_Short;
};

