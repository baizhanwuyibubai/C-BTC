#include "TradeMacd.h"
#include <locale>
#include <codecvt>
TradeMacd::TradeMacd(STR_MacdValue& MacdValue)
{
	memset(&this->m_New_BuySell, 0, sizeof(this->m_New_BuySell));
	this->m_TradeTimer = false;
	this->m_CurrentState = DK;
	this->m_MacdValue = MacdValue;
	this->m_UserMoney = this->m_MacdValue.ZiJin.ChuShiZiJin;
}

TradeMacd::~TradeMacd()
{

}

void TradeMacd::RunDuoToKong(STR_USDT& NewUSD)
{
	if (this->m_TradeTimer == true)
	{
		this->m_New_BuySell.Sell.New_Sell = OverallCurlThread()->getPrice();		//获取到最新价格
		this->m_New_BuySell.Sell.Sell_Timer = (long long)NewUSD.Base.Time;
		this->Close(this->m_New_BuySell.Sell, this->m_CurrentState);

		if (NewUSD.Is == false)
			this->m_CurrentState = Duo;
		else
			this->m_CurrentState = Kong;
		this->m_New_BuySell.Buy.New_Buy = OverallCurlThread()->getPrice();		//获取到最新价格
		this->m_New_BuySell.Buy.Buy_Timer = (long long)NewUSD.Base.Time;
		this->Open(this->m_New_BuySell.Buy, this->m_CurrentState);
	}
	else
	{
		if (NewUSD.Is == false)
			this->m_CurrentState = Duo;
		else
			this->m_CurrentState = Kong;
		this->m_New_BuySell.Buy.New_Buy = OverallCurlThread()->getPrice();		//获取到最新价格
		this->m_New_BuySell.Buy.Buy_Timer = (long long)NewUSD.Base.Time;
		this->Open(this->m_New_BuySell.Buy, this->m_CurrentState);
	}
}

void TradeMacd::SocketOpen(double New_Price, long long Timer, unsigned char CurrentState)
{
	STR_BTC_Buy Buy;
	memset(&Buy, 0, sizeof(Buy));
	Buy.BuyPrice = New_Price;
	Buy.BuyTime = Timer;
	Buy.string[0] = (CurrentState == Duo ? 0x10 : 0x11);
	
	OverallSocket()->GroupData(UI_Type::Socket_BTC_Buy, &Buy, sizeof(Buy));
}

void TradeMacd::SocketClose(double New_Price, long long Timer, double Cash, double BTC_Income, unsigned char CurrentState)
{
	STR_BTC_Sell Sell;
	memset(&Sell, 0, sizeof(Sell));
	Sell.SellPrice = New_Price;
	Sell.SellingTime = Timer;
	Sell.Cash = Cash;
	Sell.BTC_Income = BTC_Income;
	OverallSocket()->GroupData(UI_Type::Socket_BTC_Sell, &Sell, sizeof(Sell));
}

void TradeMacd::RunOpenDuo(STR_USDT& USD)
{
	if (this->m_TradeTimer == false && this->m_CurrentState == DK)
	{
		STR_New_Buy Buy;
		Buy.New_Buy = OverallCurlThread()->getPrice();
		Buy.Buy_Timer = USD.Base.Time;
		this->Open(Buy, Kong);
	}
}

void TradeMacd::Open(STR_New_Buy& Buy, unsigned char CurrentState)
{
	this->m_New_BuySell.Buy = Buy;
	this->m_CurrentState = CurrentState;
	this->SocketOpen(m_New_BuySell.Buy.New_Buy, m_New_BuySell.Buy.Buy_Timer, CurrentState);
	this->m_TradeTimer = true;
}

void TradeMacd::Close(STR_New_Sell& Sell, unsigned char CurrentState)
{
	double usdt = this->Money(CurrentState);
	this->m_New_BuySell.Sell = Sell;
	this->m_UserMoney = this->m_UserMoney + usdt;
	this->SocketClose(
		this->m_New_BuySell.Sell.New_Sell,
		this->m_New_BuySell.Sell.Sell_Timer,
		this->m_UserMoney,
		usdt,
		CurrentState);
	std::cout << this->m_UserMoney << "    " << usdt << std::endl;
	memset(&this->m_New_BuySell, 0, sizeof(this->m_New_BuySell));
}

double TradeMacd::Money(unsigned char CurrentState)
{
	double usd = this->Sell(
		m_New_BuySell.Buy.New_Buy,					//开仓价格
		m_New_BuySell.Sell.New_Sell,				//平仓价格
		m_MacdValue.ZiJin.DanBiJiaoYi,				//单笔交易
		m_MacdValue.ZiJin.GanGanLv,					//杠杆率
		m_MacdValue.ZiJin.ZuiXiaoXiaDan,			//最小下单
		CurrentState);
	return usd;
}