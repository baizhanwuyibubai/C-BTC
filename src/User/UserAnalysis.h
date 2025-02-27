#pragma once
#include "../Timer/TimerCount.h"
#include "../OverallClass/Overall.h"
#include "../TradeRun/MainTrade.h"
class UserAnalysis
{
public:
	UserAnalysis();
	~UserAnalysis();
public:
	void start();
private:
    void ThreadPrice();
	void IniSlot();
private:
	void SlotCurlGet(STR_BaseKlines& buff);
private:
	Jump::TimerCount m_TimerCount;
	MainTrade MainTrade;
	bool IsThread;
};