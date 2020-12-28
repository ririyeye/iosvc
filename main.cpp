
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
#include "udp_session.h"

using namespace boost;
using boost::asio::ip::udp;
using boost::system::error_code;

int main()
{

	try {
		boost::asio::io_service io_service;
		boost::asio::ip::udp::socket udp_server_endpoint(io_service, udp::endpoint(udp::v4(), 8888));

		//add work session
		boost::ptr_vector<UDP_SESSION> sessions;
		for (unsigned i = 0; i < boost::thread::hardware_concurrency(); i++) {
			sessions.push_back(new UDP_SESSION(udp_server_endpoint));
		}
		//add work thread
		boost::thread_group group;
		for (unsigned i = 0; i < boost::thread::hardware_concurrency();
		     ++i)
			group.create_thread(bind(&boost::asio::io_service::run,
						 boost::ref(io_service)));

		group.join_all();

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}