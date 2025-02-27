#include "RSI.h"
extern "C"
{
#include <ta_libc.h>
}
RSI::RSI(int Short) :
	m_Short(Short)
{

}

RSI::~RSI()
{

}

STR_RSI RSI::GetValue(std::vector<STR_USDT>& close, int index)
{
	double rsi[MACDSIZE];
	double Value[MACDSIZE];
	STR_RSI STR_RSI;
	TA_RetCode retcode;
	retcode = TA_Initialize();
	for (int i = 0; i < MACDSIZE; i++)
	{
		Value[i] = close[(index - MACDSIZE) + (i + 1)].Base.close;
	}
	int outBegin = 0;
	int outNbElement = 0;
	TA_RetCode result = TA_RSI(0,		// StartIdx（通常从0开始）  
		MACDSIZE - 1,					// EndIdx（最后一个数据的索引）  
		&Value[0],						// InReal（指向价格数据的指针）  
		this->m_Short,					// TimePeriod  
		&outBegin,
		&outNbElement,
		rsi);

	retcode = TA_Shutdown();
	STR_RSI.Rsi = rsi[outNbElement - 1];
	return STR_RSI;
}