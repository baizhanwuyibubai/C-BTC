#pragma once
struct STR_ZiJin
{
	double GanGanLv;		//�ܸ���
	double DanBiJiaoYi;		//���ʽ���
	double ChuShiZiJin;		//��ʼ�ʽ�
	double ZuiXiaoXiaDan;	//��С�µ�
};

struct STR_DuoKong
{
	short DuoTou;			//��ͷ
	short KongTou;			//��ͷ
	short ZhongXing;		//����
};

struct STR_MacdFile
{
	short Macd_J;
	short Macd_D;
	short Macd_K;
};

struct STR_JDK
{
	short Long_J;
	short Long_D;
	short Long_K;
};

struct STR_SRIFile
{
	double value1;
	double value2;
	double RSI;
};

struct STR_ShiPan
{
	short ShiPan;
};

struct STR_MacdValue
{
	STR_ZiJin ZiJin;
	STR_DuoKong DuoKong;
	STR_MacdFile Macd;
	STR_JDK JDK;
	STR_SRIFile SRIFile;
	STR_ShiPan ShiPan;
};