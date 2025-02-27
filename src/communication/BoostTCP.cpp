#include "BoostTCP.h"
#include <iostream>
Jump::TCP::TCP(std::string IP, short Port) : m_LocalIP(IP), m_LocalPort(Port), m_IsOpen(false)
{
	try
	{
		io_service = new boost::asio::io_service;
		myacceptor = new boost::asio::ip::tcp::acceptor(*io_service, 
			boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(m_LocalIP), m_LocalPort));
		socket = new boost::asio::ip::tcp::socket(*io_service);
		myacceptor->accept(*socket);
		std::cout << "IP    " << socket->remote_endpoint().address() <<"   " << socket->remote_endpoint().port() << "   Port" << std::endl;
		std::cout << socket->is_open() << std::endl;
		m_IsOpen = true;
	}
	catch (boost::exception const& e)
	{
		io_service = nullptr;
		socket = nullptr;
		m_IsOpen = false;
		std::cout << "socket 创建错误******" << boost::diagnostic_information(e) << std::endl;
	}
}

int Jump::TCP::Write(char* buff, int Len)
{
	if (socket == nullptr)
		return 0;
	boost::system::error_code error;
	int len = 0;
	try
	{
		//len = (int)socket->read_some(boost::asio::buffer(buff, Len), error);
		len = (int)socket->write_some(boost::asio::buffer(buff, Len), error);
		return len;
	}
	catch (boost::exception const& e)
	{
		std::cout << "Write socket error" << boost::diagnostic_information(e) << std::endl;
		return len;
	}
}

int Jump::TCP::Write(const char* buff, int Len)
{
	if (socket == nullptr)
		return 0;
	boost::system::error_code error;
	int len = 0;
	try
	{
		len = (int)socket->write_some(boost::asio::buffer(buff, Len), error);
		return len;
	}
	catch (boost::exception const& e)
	{
		std::cout << "Write socket error" << boost::diagnostic_information(e) << std::endl;
		return len;
	}
}

int Jump::TCP::Read(char* buf, int Len)
{
	if (socket == nullptr)
		return 0;

	int len = 0;
	try
	{
		boost::system::error_code error;
		len = (int)socket->read_some(boost::asio::buffer(buf, Len), error);
		return len;
	}
	catch (boost::exception const& e)
	{
		//std::cout << "Read socket error" << boost::diagnostic_information(e) << std::endl;
		e;
		return len;
	}
}

Jump::TCP::~TCP()
{
	delete socket;
}

bool Jump::TCP::IsTCPOpen()
{
	return m_IsOpen;
}