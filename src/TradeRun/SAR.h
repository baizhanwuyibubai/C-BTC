#pragma once
//#include "..\..\APP\Chart\qcustomplot.h"
#include <vector>
#include "../OverallClass/NetworkStrData.h"
class SAR
{
public:
	SAR(double value1, double value2);
	~SAR();
public:
	STR_Sar GetValue(std::vector<STR_USDT>& close, int index);
private:
	double value1;
	double value2;
};

