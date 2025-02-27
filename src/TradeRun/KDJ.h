#pragma once
//#include "..\..\APP\Chart\qcustomplot.h"
#include <vector>
#include "../OverallClass/NetworkStrData.h"
class KDJ
{
public:
	KDJ(int K = 9, int D = 3, int J = 3); //BTC参数
	~KDJ();
public:
	STR_KDJ GetValue(std::vector<STR_USDT>& close, int index);
private:
	int m_K;
	int m_D;
	int m_J;
};

