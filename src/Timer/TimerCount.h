#pragma once
#include <string>
namespace Jump
{
	struct STR_Timer
	{
		short Year;		   //年份
		short Mon;		   //星期
		short Mday;		   //日
		short Hour;		   //小时
		short Min;		   //分钟
		short Sec;		   //毫秒
	};
	class TimerCount
	{
	public:
		TimerCount();
		~TimerCount();
	public:
		unsigned long long Count();
		std::string getTimer();
		unsigned long long getTimerUTC();
		STR_Timer getSTRTimer();
		void Sleep(int Ms);
	private:
		void Thread();
	private:
		unsigned long long m_Count;
		bool IsThread;
	};
}