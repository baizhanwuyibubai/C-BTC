#include <iomanip>
#include "Algorithm.h"

Algorithm::Algorithm(double commission)
{
	m_Commission = commission;
}

Algorithm::~Algorithm()
{

}

double Algorithm::Average(double* Value, int End, int Begin)
{
	if (Begin == 0)
	{
		double Value = 0;
		for (int i = 0; i < End; i++)
		{
			Value += Value;
		}
		return Value / End;
	}
	return 0.0;
}

double Algorithm::Max(double* Value, int End, int Begin)
{
	double maxVal = Value[0]; // 假设第一个元素是最大的
	for (int i = 1; i < End; ++i)
	{
		if (Value[i] > maxVal)
		{
			maxVal = Value[i]; // 更新最大值
		}
	}
	return maxVal;
}

double Algorithm::Min(double* Value, int End, int Begin)
{
	double maxVal = Value[0]; // 假设第一个元素是最大的
	for (int i = 1; i < End; ++i)
	{
		if (Value[i] < maxVal)
		{
			maxVal = Value[i]; // 更新最大值
		}
	}
	return maxVal;
}

double Algorithm::Buy(double NewPrice, double USD, double lever)
{
	double ParValue = double(double(1 / NewPrice) * 10000);
	ParValue = double(ParValue * 0.0001);
	double BTC = double(ParValue * (USD * lever));
	return BTC;
}

double Algorithm::ParValueToUSD(double NewPrice, double USD, double lever)
{
	double ParValue = int(double(1 / NewPrice) * 10000);
	ParValue = double(ParValue * 0.0001);
	double BTC = double(ParValue * (USD * lever));
	BTC = NewPrice * BTC;
	return BTC;
}

double Algorithm::Sell(double Price, double NewPrice, double volume, double lever, double fenbianlv, unsigned char Is)
{
	double ShouXuFei = ((volume * lever) * m_Commission) * 2;
	double Contract = countDecimalPlaces(this->Buy(Price, volume, lever), fenbianlv);
	double income = 0;
	if (Is == Duo)
		income = (Contract * NewPrice) - (Contract * Price);//做多
	else if (Is == Kong)
		income = (Contract * Price) - (Contract * NewPrice);//做空

	return income - ShouXuFei;
}

double Algorithm::Commission(double volume, double lever)
{
	return ((volume * lever) * m_Commission) * 2;
}

double Algorithm::Percentage(double Value, double NewValue)
{
	return (Value / NewValue) * 100;
}

CrossType Algorithm::check_cross(double prev_diff, double prev_dea, double curr_diff, double curr_dea)
{
	if (prev_diff > prev_dea && curr_diff <= curr_dea)
	{
		return CrossType::DOWN; // 下降交叉
	}
	else if (prev_diff < prev_dea && curr_diff >= curr_dea)
	{
		return CrossType::UP; // 上升交叉
	}
	return CrossType::NONEE; // 无交叉
}

double Algorithm::countDecimalPlaces(double num, double fenbianlv)
{
	int value = int(num / fenbianlv);
	double number = value * fenbianlv;
	return number;
}