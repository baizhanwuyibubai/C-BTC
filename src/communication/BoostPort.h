#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
namespace Jump
{
	class Port
	{
	public:
		Port();
		~Port();
	public:
		int Write(char* buff, int Len);
		bool init_port(std::string PortName, int Baud_Rrate);
	protected:
		int Read(char* buf, int Len);
		void handle_read(char buf[], boost::system::error_code ec, std::size_t bytes_transferred);
	private:
		boost::asio::io_service* io_service;
		boost::asio::serial_port* pSerialPort;
	};
}