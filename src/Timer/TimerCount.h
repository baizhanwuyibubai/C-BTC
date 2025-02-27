#pragma once
#include <string>
namespace Jump
{
	struct STR_Timer
	{
		short Year;		   //���
		short Mon;		   //����
		short Mday;		   //��
		short Hour;		   //Сʱ
		short Min;		   //����
		short Sec;		   //����
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