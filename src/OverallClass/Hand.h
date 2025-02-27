#pragma once
#ifdef _WIN32
#define LocalIP "127.0.0.1"
#define LocalPort 8090

#define SendIP "127.0.0.1"
#define SendPort 8080
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS模拟器
#elif TARGET_OS_IPHONE
// iOS设备
#else
// MacOS
#endif
#elif defined(__linux__)
#define LocalIP "192.168.1.245"
#define LocalPort 8090

#define SendIP "192.168.1.240"
#define SendPort 8080
#elif defined(__unix__)
// 其他Unix系统
#else
// 其他系统
#endif

#include "NetworkStrData.h"

#define UIIP "127.0.0.1"
#define UILocalPort 10000
#define UISendPort 11000


#define FAPI "/fapi/v1/"
#define 期货API std::string("https://fapi.binance.com") + std::string(FAPI)
#define 期货K线 "klines?symbol="
#define 期货最新价 "ticker/price?symbol="
#define 服务器时间 "time"

#define Duo					(unsigned char)0x10				//做多
#define Kong				(unsigned char)0x11				//做空
#define DK					(unsigned char)0x13				//初始状态
#define VeSizeMax 500
#define DuoKongMax 480