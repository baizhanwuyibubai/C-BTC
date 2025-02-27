#include "KDJ.h"
extern "C"
{
#include <ta_libc.h>
}
KDJ::KDJ(int K, int D, int J) :
	m_K(K), m_D(D), m_J(J)
{

}

KDJ::~KDJ()
{

}

STR_KDJ KDJ::GetValue(std::vector<STR_USDT>& close, int index)
{
	double Value[MACDSIZE];
	STR_KDJ STR_KDJ{};
	memset(&STR_KDJ, 0, sizeof(STR_KDJ));
	TA_RetCode retcode;
	retcode = TA_Initialize();
	for (int i = 0; i < MACDSIZE; i++)
	{
		Value[i] = close[(index - MACDSIZE) + (i + 1)].Base.close;
	}
	int outBegin = 0;
	int outNbElement = 0;
	//TA_RetCode result = TA_RSI(0,		// StartIdx（通常从0开始）  
	//	MACDSIZE - 1,					// EndIdx（最后一个数据的索引）  
	//	&Value[0],						// InReal（指向价格数据的指针）  
	//	this->m_Short,					// TimePeriod  
	//	&outBegin,
	//	&outNbElement,
	//	rsi);
	//retcode = TA_Shutdown();
	//STR_RSI.Rsi = rsi[outNbElement - 1];
	return STR_KDJ;
}