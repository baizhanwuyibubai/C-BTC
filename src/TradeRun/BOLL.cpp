#include "BOLL.h"
extern "C"
{
#include <ta_libc.h>
}
BOLL::BOLL()
{

}

BOLL::BOLL(double value1, double value2)
{
	this->value1 = value1;
	this->value2 = value2;
}

BOLL::~BOLL()
{

}

STR_BOLL BOLL::GetValue(std::vector<STR_USDT>& close, int index)
{

	double closePrices[MACDSIZE];
	STR_BOLL STR_BOLL;
	// 用于存储计算结果的数组
	double upperBand[MACDSIZE], middleBand[MACDSIZE], lowerBand[MACDSIZE];
	memset(upperBand, 0, sizeof(upperBand));
	memset(middleBand, 0, sizeof(middleBand));
	memset(lowerBand, 0, sizeof(lowerBand));
	// TA-Lib函数需要的参数
	int outBegIdx, outNbElement;
	for (int i = 0; i < MACDSIZE; i++)
	{
		closePrices[i] = close[(index - MACDSIZE) + (i + 1)].Base.open;
	}
	// 调用布林带函数
	// 注意：这里使用的函数名和参数可能根据TA-Lib的版本和你的环境有所不同
	// 示例中使用的函数名和参数仅为示意，具体请参考TA-Lib的文档

	TA_RetCode result = TA_BBANDS(
		0, // StartIdx
		MACDSIZE - 1, // EndIdx
		closePrices, // Open prices array
		30, // Size of open prices array
		21.0, // Time period
		2.0, // Deviations up (or down)
		TA_MAType::TA_MAType_WMA, // MA type
		&outBegIdx,
		&outNbElement,
		upperBand,
		middleBand,
		lowerBand);
	STR_BOLL.MiddleBand = middleBand[outNbElement - 1];
	STR_BOLL.UpperBand = upperBand[outNbElement - 1];
	STR_BOLL.LowerBand = lowerBand[outNbElement - 1];
	return STR_BOLL;
}