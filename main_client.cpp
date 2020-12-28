

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

using namespace boost;
using boost::asio::ip::udp;
using boost::system::error_code;

int main()
{

	try {
		boost::asio::io_service  io_service;
		boost::asio::ip::udp::socket udp_socket(io_service, boost::asio::ip::udp::v4());

		//add work session
 		udp_socket.send_to(
                boost::asio::buffer("Hello world!"),
                boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("139.180.204.124"), 8888});

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}