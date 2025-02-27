#pragma once
#include "../communication/InputToOutput.h"
#include "../communication/QCurl.h"
#include "../Timer/TimerCount.h"
#include "../User/CurlThread.h"

InputToOutput* OverallSocket();				//向外发送数据
QCulReadClass* OverallCurl();				//对外Curl
CurlThread* OverallCurlThread();			//获取BTC数据
Jump::TimerCount* OverallTimer();			//定时器