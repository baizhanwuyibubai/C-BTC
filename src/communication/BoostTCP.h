#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
struct STR_Input_Data
{
	char buff[1024];
	int Len;
	bool Is;
};
namespace Jump
{
	class TCP
	{
	public:
		TCP(std::string IP = "", short Port = 0);
		~TCP();
	public:
		bool IsTCPOpen();
		int Write(char* buff, int Len);
		int Write(const char* buff, int Len);
		int Read(char* buf, int Len);
	private:
		boost::asio::io_service* io_service;
		boost::asio::ip::tcp::socket* socket;
		boost::asio::ip::tcp::acceptor* myacceptor;
		std::string m_LocalIP;
		short m_LocalPort;
		bool m_IsOpen;
	};
}