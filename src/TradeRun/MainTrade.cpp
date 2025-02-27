#include "MainTrade.h"
#include "../communication/Json.h"
#include "MACD.h"
#include "KDJ.h"
#include "RSI.h"
#include "BOLL.h"
MainTrade::MainTrade()
{
	JsonReadFileValue();
	m_Trade = new TradeMacd(m_MacdValue);
}

MainTrade::~MainTrade()
{

}

void MainTrade::Push(STR_USDT& buff)
{
	if (m_Long.size() != 0)
		OverallSocket()->GroupData(UI_Type::Socket_USDT_CurlData, &m_Long[m_Long.size() - 1], sizeof(STR_USDT));
	this->MoveData(m_Long, buff);
	//m_Trade->RunDuoToKong(buff);
	this->RunTrade(m_Long, buff);

}

void MainTrade::JsonReadFileValue()
{
	std::string FileName = "Ini/Macd值.json";

	m_MacdValue.ZiJin.GanGanLv = std::atof(Jump::JsonRead(FileName, "杠杆率").c_str());
	m_MacdValue.ZiJin.DanBiJiaoYi = std::atof(Jump::JsonRead(FileName, "单笔交易").c_str());
	m_MacdValue.ZiJin.ChuShiZiJin = std::atof(Jump::JsonRead(FileName, "初始资金").c_str());
	m_MacdValue.ZiJin.ZuiXiaoXiaDan = std::atof(Jump::JsonRead(FileName, "最小下单").c_str());

	m_MacdValue.DuoKong.DuoTou = std::atoi(Jump::JsonRead(FileName, "多头").c_str());
	m_MacdValue.DuoKong.KongTou = std::atoi(Jump::JsonRead(FileName, "空头").c_str());
	m_MacdValue.DuoKong.ZhongXing = std::atoi(Jump::JsonRead(FileName, "中性").c_str());

	m_MacdValue.Macd.Macd_J = std::atoi(Jump::JsonRead(FileName, "Macd_J").c_str());
	m_MacdValue.Macd.Macd_D = std::atoi(Jump::JsonRead(FileName, "Macd_D").c_str());
	m_MacdValue.Macd.Macd_K = std::atoi(Jump::JsonRead(FileName, "Macd_K").c_str());

	m_MacdValue.JDK.Long_J = std::atoi(Jump::JsonRead(FileName, "Long_J").c_str());
	m_MacdValue.JDK.Long_D = std::atoi(Jump::JsonRead(FileName, "Long_D").c_str());
	m_MacdValue.JDK.Long_K = std::atoi(Jump::JsonRead(FileName, "Long_K").c_str());

	m_MacdValue.SRIFile.value1 = std::atof(Jump::JsonRead(FileName, "value1").c_str());
	m_MacdValue.SRIFile.value2 = std::atof(Jump::JsonRead(FileName, "value2").c_str());
	m_MacdValue.SRIFile.RSI = std::atof(Jump::JsonRead(FileName, "RSI").c_str());

	m_MacdValue.ShiPan.ShiPan = std::atoi(Jump::JsonRead(FileName, "实盘").c_str());
}

void MainTrade::Pretreatment(std::vector<STR_USDT>& ve)
{
	int VeIndex = (int)ve.size() - 1;

	MACD Macd(m_MacdValue.Macd.Macd_J, m_MacdValue.Macd.Macd_D, m_MacdValue.Macd.Macd_K);
	KDJ kdj(m_MacdValue.JDK.Long_J, m_MacdValue.JDK.Long_D, m_MacdValue.JDK.Long_K);
	BOLL boll;
	ve[VeIndex].Macd = Macd.GetValue(ve, VeIndex);
	ve[VeIndex].kdj = kdj.GetValue(ve, VeIndex);
	ve[VeIndex].BOLL = boll.GetValue(ve, VeIndex);
}

void MainTrade::MoveData(std::vector<STR_USDT>& ve, STR_USDT& base)
{
	if (VeSizeMax <= ve.size())
	{
		for (int i = 1; i < ve.size(); i++)
		{
			ve[i - 1] = ve[i];
		}
		ve[ve.size() - 1] = base;
		Pretreatment(ve);
	}
	else
	{
		ve.push_back(base);
	}
}

void MainTrade::RunTrade(std::vector<STR_USDT>& ve, STR_USDT& NewUSD)
{
	Jump::STR_Timer Timer = OverallTimer()->getSTRTimer();
	int iDuo = 0;
	int iKong = 0;
	if (Timer.Hour == 0 ||
		Timer.Hour == 8 ||
		Timer.Hour == 16)
	{
		if (Timer.Min == 0)
		{
			std::cout << "当前时间: " << Timer.Year << "-"
				<< Timer.Mon + 1 << "-"
				<< Timer.Mday << " "
				<< Timer.Hour << ":"
				<< Timer.Min << ":"
				<< Timer.Sec << std::endl;
			if (DuoKongMax <= ve.size())
			{
				int IndexDuoKong = (int)ve.size() - DuoKongMax;
				if (0 < IndexDuoKong)
				{
					for (int i = IndexDuoKong; i < ve.size() - 2; i++)
					{
						if (ve[i].Base.close < ve[i + 1].Base.close)
							iDuo++;
						else
							iKong++;
					}
				}
			}
			//NewUSD.Is = iDuo > iKong ? true : false;//1
			//NewUSD.Is = iDuo > iKong ? false : true;//2
			NewUSD.Is = iDuo > iKong ? true : false;
			m_Trade->RunDuoToKong(NewUSD);
		}
	}

}