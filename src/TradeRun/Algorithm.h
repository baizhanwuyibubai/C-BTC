#pragma once
enum CrossType { NONEE, UP, DOWN };
#include "../OverallClass/Hand.h"
class Algorithm
{
public:
	Algorithm(double commission = 0.0004);
	//Algorithm(double commission = 0.0000);
	~Algorithm();
public:
	double Average(double* Value, int End, int Begin = 0);
	double Max(double* Value, int End, int Begin = 0);
	double Min(double* Value, int End, int Begin = 0);
	double Buy(double NewPrice, double USD, double lever);											//买入股票
	double Sell(double Price, double NewPrice, double volume, double lever, double fenbianlv, unsigned char Is);		//卖出股票
	double Commission(double volume, double lever);													//手续费
	double ParValueToUSD(double NewPrice, double USD, double lever);								//张转USD
	double Percentage(double Value, double NewValue);												//盈利百分比
	CrossType check_cross(double prev_diff, double prev_dea, double curr_diff, double curr_dea);
	double countDecimalPlaces(double num, double fenbianlv);
private:
	double m_Commission;
};

