#include "UserAnalysis.h"
#include "../OverallClass/Hand.h"


UserAnalysis::UserAnalysis() : IsThread(true)
{

}

UserAnalysis::~UserAnalysis()
{
	this->IsThread = false;
}

void UserAnalysis::start()
{
	IniSlot();
	std::thread t1(&UserAnalysis::ThreadPrice, this);
	t1.detach();
}

void UserAnalysis::ThreadPrice()
{
	STR_BTC_Price Price;
	while (this->IsThread)
	{
		try
		{
			Price.Price = OverallCurlThread()->getPrice();
			OverallSocket()->GroupData(UI_Type::Socket_BTC_Price, &Price, sizeof(STR_BTC_Price));
		}
		catch (boost::exception const& e)
		{
			std::cout << "Analysys error" << boost::diagnostic_information(e) << std::endl;
		}
		this->m_TimerCount.Sleep(500);
	}
}

void UserAnalysis::IniSlot()
{
	OverallCurlThread()->SignalsData.connect(boost::bind(&UserAnalysis::SlotCurlGet, this, std::placeholders::_1));
}

void UserAnalysis::SlotCurlGet(STR_BaseKlines& buff)
{
	STR_USDT USDT;
	memset(&USDT, 0, sizeof(STR_USDT));
	USDT.Base = buff;
	MainTrade.Push(USDT);
}
