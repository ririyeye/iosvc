//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "udp_session.h"

using namespace boost;
using boost::asio::ip::udp;
using boost::system::error_code;

class udp_server {
    public:
	udp_server(boost::asio::io_service &io_context, int port)
		: socket_(io_context, udp::endpoint(udp::v4(), port))
	{
		UDP_SESSION::start_new_receive(socket_);
	}
	udp::socket socket_;
};

int main()
{
	try {
		boost::asio::io_service io_service;
		udp_server server(io_service, 8888);

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