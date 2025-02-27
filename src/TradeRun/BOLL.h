#pragma once
//#include "..\..\APP\Chart\qcustomplot.h"
#include <vector>
#include "../OverallClass/NetworkStrData.h"
class BOLL
{
public:
	BOLL();
	BOLL(double value1, double value2);
	~BOLL();
public:
	STR_BOLL GetValue(std::vector<STR_USDT>& close, int index);
private:
	double value1;
	double value2;
};

