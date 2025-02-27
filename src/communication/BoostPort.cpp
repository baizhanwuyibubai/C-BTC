#include "BoostPort.h"
Jump::Port::Port()
{
	try
	{
		io_service = new boost::asio::io_service;
		pSerialPort = new boost::asio::serial_port(*io_service);
	}
	catch (boost::exception const& e)
	{
		io_service = nullptr;
		pSerialPort = nullptr;
		std::cout << "Port error" << boost::diagnostic_information(e) << std::endl;
	}
}

Jump::Port::~Port()
{

}

bool Jump::Port::init_port(std::string PortName, int Baud_Rrate)
{
	boost::system::error_code m_ec;
	if (!pSerialPort)
	{
		return false;
	}
	try
	{
		pSerialPort->open(PortName, m_ec);

		pSerialPort->set_option(boost::asio::serial_port::baud_rate(Baud_Rrate), m_ec);
		pSerialPort->set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none), m_ec);
		pSerialPort->set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none), m_ec);
		pSerialPort->set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one), m_ec);
		pSerialPort->set_option(boost::asio::serial_port::character_size(8), m_ec);
		return true;
	}
	catch (boost::exception const& e)
	{
		std::cout << "Port error" << boost::diagnostic_information(e) << std::endl;
		return false;
	}
}

int Jump::Port::Write(char* buff, int Len)
{
	try
	{
		size_t len = boost::asio::write(*pSerialPort, boost::asio::buffer(buff, Len));
		return (int)len;
	}
	catch (boost::exception const& e)
	{
		std::cout << "Port write error" << boost::diagnostic_information(e) << std::endl;
		return false;
	}
}

int Jump::Port::Read(char* buf, int Len)
{
	int len = 0;
	try
	{
		boost::asio::async_read(*pSerialPort, boost::asio::buffer(buf, Len));
		len = (int)boost::asio::read(*pSerialPort, boost::asio::buffer(buf, 10));
		return len;
	}
	catch (boost::exception const& e)
	{
		std::cout << "read Port Error" << boost::diagnostic_information(e) << std::endl;
		return len;
	}
}

void Jump::Port::handle_read(char buf[], boost::system::error_code ec, std::size_t bytes_transferred)
{
	std::cout.write(buf, bytes_transferred);
}