#include "SAR.h"
extern "C"
{
#include <ta_libc.h>
}
SAR::SAR(double value1, double value2)
{
	this->value1 = value1;
	this->value2 = value2;
}

SAR::~SAR()
{

}

STR_Sar SAR::GetValue(std::vector<STR_USDT>& close, int index)
{
	int start = 0;
	int End = 0;
	STR_Sar Sar;
	TA_RetCode retcode;
	retcode = TA_Initialize();
	double high[MACDSIZE], low[MACDSIZE];
	double out[MACDSIZE];
	memset(high, 0, sizeof(high));
	memset(low, 0, sizeof(low));
	memset(out, 0, sizeof(out));
	for (int i = 0; i < MACDSIZE; i++)
	{
		high[i] = close[(index - MACDSIZE) + (i + 1)].Base.high;
		low[i] = close[(index - MACDSIZE) + (i + 1)].Base.low;
	}
	TA_SAR(0, MACDSIZE - 1, high, low, this->value1, this->value2, &start, &End, out);
	Sar.SAR = out[End - 1];
	retcode = TA_Shutdown();
	return Sar;
}