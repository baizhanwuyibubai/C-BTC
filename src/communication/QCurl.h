#pragma once
#include <string>
#define CURL_STATICLIB
#include <curl.h>
class QCulReadClass
{
public:
	QCulReadClass();
	~QCulReadClass();
	bool Get(std::string& Buff, std::string& Curl);
	bool Post(std::string& url, std::string& post_data, std::string& buff);
private:
};