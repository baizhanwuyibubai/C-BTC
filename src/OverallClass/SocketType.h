#pragma once
#define INITIAL 0x99
struct STR_Initial
{
	short OneWord;
	short Type;
	int SocketSize;
};

struct STR_SocketData
{
	STR_Initial Initial;
	char buff[1024];
};

struct STR_BTC_Buy
{
	unsigned long long BuyTime;			//����ʱ��
	double BuyPrice;					//����۸�
	char string[20];
};

struct STR_BTC_Sell
{
	unsigned long long SellingTime;		//����ʱ��
	double SellPrice;					//�������̼�

	double BTC_Income;					//����
	double Cash;						//�ֽ���
};

struct STR_End
{
	char end;
};

enum UI_Type
{
	Socket_BaseKlines_CurlData = 0x100,
	Socket_USDT_CurlData = 0x101,
	Socket_BTC_Buy = 0x200,
	Socket_BTC_Sell = 0x201,
	Socket_BTC_Price = 0x202,
	Socket_End = 0xFF
};