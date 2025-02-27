#include "MACD.h"
extern "C"
{
#include <ta_libc.h>
}
MACD::MACD(int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod) :
	m_OptInFastPeriod(optInFastPeriod),
	m_OptInSlowPeriod(optInSlowPeriod),
	m_OptInSignalPeriod(optInSignalPeriod)
{

}

MACD::~MACD()
{

}

STR_Macd MACD::GetValue(std::vector<STR_USDT>& close, int index)
{
	int ret_code = 0;
	int out_beg = 0, out_nb_element = 0;
	double Value[MACDSIZE];
	TA_RetCode retcode;
	STR_Macd STR_Macd;
	retcode = TA_Initialize();
	double d1[MACDSIZE], d2[MACDSIZE], d3[MACDSIZE];
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d1));
	memset(d3, 0, sizeof(d1));
	for (int i = 0; i < MACDSIZE; i++)
	{
		Value[i] = close[(index - MACDSIZE) + (i + 1)].Base.close;
	}
	TA_MACD(0, MACDSIZE - 1, Value, m_OptInFastPeriod, m_OptInSlowPeriod, m_OptInSignalPeriod, &out_beg, &out_nb_element, d1, d2, d3);

	if (out_nb_element != 0)
	{
		STR_Macd.Macd = d1[out_nb_element - 1];
		STR_Macd.Signal = d2[out_nb_element - 1];//decimalNormalize(d1[out_nb_element - 1], Min(d1, out_nb_element), Max(d1, out_nb_element));
		STR_Macd.Histogram = d3[out_nb_element - 1];
	}
	retcode = TA_Shutdown();
	return STR_Macd;
}