#pragma once
#define MACDSIZE 500
struct STR_BOLL
{
	double UpperBand;
	double MiddleBand;
	double LowerBand;
};

struct STR_Macd
{
	double Macd;
	double Signal;
	double Histogram;
};

struct STR_Sar
{
	double SAR;
};

struct STR_RSI
{
	double Rsi;
};

struct STR_KDJ
{
	double K;
	double D;
	double J;
};

struct STR_BTC_Price
{
	double Price;
};

struct STR_BaseKlines
{
	unsigned long long Time;	//时间
	double open;				//开盘
	double high;				//最高
	double low;					//最低
	double close;				//收盘
};

struct STR_New_Buy
{
	double New_Buy;
	long long Buy_Timer;
};

struct STR_New_Sell
{
	double New_Sell;
	long long Sell_Timer;
};

struct STR_BTC_New_Buy_Sell
{
	STR_New_Buy Buy;
	STR_New_Sell Sell;
};

struct STR_USDT
{
	bool Is;
	STR_BaseKlines Base;
	STR_BOLL BOLL;
	STR_Macd Macd;
	STR_Sar Sar;
	STR_RSI Rsi;
	STR_KDJ kdj;
};