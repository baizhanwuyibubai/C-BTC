#include "BoostUDP.h"

Jump::UDP::UDP(std::string IP, short Port) : m_LocalIP(IP), m_LocalPort(Port), m_IsOpen(false)
{
	try
	{
		io_service = new boost::asio::io_service;
		socket = new boost::asio::ip::udp::socket(*io_service,
			boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(m_LocalIP), m_LocalPort));
		std::cout << socket->is_open() << std::endl;
		m_IsOpen = true;
	}
	catch (boost::exception const& e)
	{
		io_service = nullptr;
		socket = nullptr;
		m_IsOpen = false;
		std::cout << "socket 创建错误" << boost::diagnostic_information(e) << std::endl;
	}
}

int Jump::UDP::Write(char* buff, int Len, std::string sendIP, short sendPort)
{
	if (socket == nullptr)
		return 0;
	boost::asio::ip::udp::endpoint receive_endpoint(
		boost::asio::ip::address::from_string(sendIP), sendPort);
	boost::system::error_code error;
	int len = 0;
	try
	{
		len = (int)socket->send_to(boost::asio::buffer(buff, Len), receive_endpoint, 0, error);
		return len;
	}
	catch (boost::exception const& e)
	{
		std::cout << "Write socket error" << boost::diagnostic_information(e) << std::endl;
		return len;
	}
}

int Jump::UDP::Read(char* buf, int Len)
{
	if (socket == nullptr)
		return 0;

	int len = 0;
	try
	{
		socket->async_receive(boost::asio::buffer(buf, Len));
		len = (int)socket->receive(boost::asio::buffer(buf, Len));
		return len;
	}
	catch (boost::exception const& e)
	{
		//std::cout << "Read socket error" << boost::diagnostic_information(e) << std::endl;
		e;
		return len;
	}
}

Jump::UDP::~UDP()
{
	delete socket;
}

bool Jump::UDP::IsUDPOpen()
{
	return m_IsOpen;
}