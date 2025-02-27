#include "QCurl.h"
#define API_KEY 		"X-MBX-APIKEY: IE4MCodRJKvFJGJsfdHGdGqHdpIpOmdgwcvG7RW9t98w7a1fxpOsQDWuouMIKI25"
#define CURL_STATICLIB
#include <curl.h>
CURL* m_Curl;
CURLcode m_Res;
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s)
{
	size_t newLength = size * nmemb;
	try {
		s->append((char*)contents, newLength);
	}
	catch (std::bad_alloc& e) 
	{
		// handle memory problem
		e;
		return 0;
	}
	return newLength;
}

QCulReadClass::QCulReadClass()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_Res = CURLE_OK;
	m_Curl = curl_easy_init();
}

QCulReadClass::~QCulReadClass()
{

}

bool QCulReadClass::Get(std::string& Buff, std::string& Curl)
{
	if (m_Curl)
	{
		curl_easy_setopt(m_Curl, CURLOPT_URL, Curl.c_str());
		curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, &Buff);
		m_Res = curl_easy_perform(m_Curl);
	}
	return m_Res;
}

bool QCulReadClass::Post(std::string& url, std::string& post_data, std::string& buff)
{
	CURLcode res;
	std::string string;
	std::string extra_http_header(API_KEY);
	if (m_Curl) {

		curl_easy_setopt(m_Curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, &buff);
		curl_easy_setopt(m_Curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(m_Curl, CURLOPT_ENCODING, "gzip");
		if (post_data.size() != 0)
		{
			struct curl_slist* chunk = NULL;
			chunk = curl_slist_append(chunk, extra_http_header.c_str());
			curl_easy_setopt(m_Curl, CURLOPT_HTTPHEADER, chunk);
		}
	}
	curl_easy_setopt(m_Curl, CURLOPT_POSTFIELDS, post_data.c_str());
	res = curl_easy_perform(m_Curl);
	return res;
}