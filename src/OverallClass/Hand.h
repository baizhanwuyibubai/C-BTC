#pragma once
#ifdef _WIN32
#define LocalIP "127.0.0.1"
#define LocalPort 8090

#define SendIP "127.0.0.1"
#define SendPort 8080
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOSģ����
#elif TARGET_OS_IPHONE
// iOS�豸
#else
// MacOS
#endif
#elif defined(__linux__)
#define LocalIP "192.168.1.245"
#define LocalPort 8090

#define SendIP "192.168.1.240"
#define SendPort 8080
#elif defined(__unix__)
// ����Unixϵͳ
#else
// ����ϵͳ
#endif

#include "NetworkStrData.h"

#define UIIP "127.0.0.1"
#define UILocalPort 10000
#define UISendPort 11000


#define FAPI "/fapi/v1/"
#define �ڻ�API std::string("https://fapi.binance.com") + std::string(FAPI)
#define �ڻ�K�� "klines?symbol="
#define �ڻ����¼� "ticker/price?symbol="
#define ������ʱ�� "time"

#define Duo					(unsigned char)0x10				//����
#define Kong				(unsigned char)0x11				//����
#define DK					(unsigned char)0x13				//��ʼ״̬
#define VeSizeMax 500
#define DuoKongMax 480