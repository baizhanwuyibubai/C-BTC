#include "TimerCount.h"
#include "../OverallClass/Hand.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>
#include <chrono>
#define TIMER_MS 50
Jump::TimerCount::TimerCount() : m_Count(0), IsThread(true)
{
	std::thread t1(&TimerCount::Thread, this);
	t1.detach();
}

Jump::TimerCount::~TimerCount()
{
	this->IsThread = false;
}

unsigned long long Jump::TimerCount::Count()
{
	return this->m_Count;
}

void Jump::TimerCount::Thread()
{
	long long Down = 0;
	std::chrono::system_clock::time_point now;
	std::chrono::system_clock::duration duration;
	while (IsThread)
	{
		now = std::chrono::system_clock::now();		// 获取当前时间点
		duration = now.time_since_epoch();			// 获取时间点与 UNIX 时间原点之间的时间间隔
		long long NewTimer = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(); // 转换为毫秒级的时间戳
		if (NewTimer >= Down)
		{
			Down = NewTimer + TIMER_MS;
			std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_MS - 5));
			this->m_Count++;
		}
	}
}

std::string Jump::TimerCount::getTimer()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	std::string string = now.zone_as_posix_string();
	return string;
}

unsigned long long Jump::TimerCount::getTimerUTC()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::system_clock::duration duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void Jump::TimerCount::Sleep(int Ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(Ms));
}

Jump::STR_Timer Jump::TimerCount::getSTRTimer()
{
	STR_Timer STR_Timer;
	std::time_t now = std::time(nullptr);

	// 转换为tm结构体
	std::tm* now_tm = std::localtime(&now);

	// 输出转换后的时间
	STR_Timer.Year = now_tm->tm_year + 1900;
	STR_Timer.Mon = now_tm->tm_mon + 1;
	STR_Timer.Mday = now_tm->tm_mday;
	STR_Timer.Hour = now_tm->tm_hour;
	STR_Timer.Min = now_tm->tm_min;
	STR_Timer.Sec = now_tm->tm_sec;

	return STR_Timer;
}