#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>

namespace Jump
{
	class UDP
	{
	public:
		UDP(std::string IP = "", short Port = 0);
		~UDP();
	public:
		bool IsUDPOpen();
		int Write(char* buff, int Len, std::string sendIP, short sendPort);
		int Read(char* buf, int Len);
	private:
		boost::asio::io_service* io_service;
		boost::asio::ip::udp::socket* socket;
		std::string m_LocalIP;
		short m_LocalPort;
		bool m_IsOpen;
	};
}