#ifndef __iot_client_session_h____
#define __iot_client_session_h____
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>

class IOT_BASE {
    public:
	IOT_BASE(
		boost::asio::io_service &in_io_svc, boost::asio::ip::address addr, int port)
		: io_service(in_io_svc), udp_socket(io_service, boost::asio::ip::udp::v4()), udp_ep(addr, port), timer(io_service)
	{
	}

    protected:
	boost::asio::io_service &io_service;
	boost::asio::ip::udp::socket udp_socket;
	boost::asio::ip::udp::endpoint udp_ep;
	boost::asio::deadline_timer timer;
};

#endif
