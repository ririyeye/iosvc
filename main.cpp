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

using namespace boost;
using boost::asio::ip::udp;
using boost::system::error_code;

boost::shared_ptr<std::string> make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return boost::make_shared<std::string>(ctime(&now));
}


class udp_server {
    public:
	udp_server(boost::asio::io_service &io_context, int port)
		: socket_(io_context, udp::endpoint(udp::v4(), port))
	{
		start_receive();
	}

    private:
	void start_receive()
	{
		auto ep = make_shared<udp::endpoint>();
		socket_.async_receive_from(
			boost::asio::buffer(recv_buffer_), *ep,
			boost::bind(
				&udp_server::handle_receive, this,
				ep,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
				));
	}

	void handle_receive(
				boost::shared_ptr<udp::endpoint> ep,
				const boost::system::error_code &error,
			    std::size_t /*bytes_transferred*/
				)
	{
		if (!error) {
			
			boost::shared_ptr<std::string> message(
				make_daytime_string());
			printf("in = %s\n",message->c_str());
			auto ep = make_shared<udp::endpoint>();
			socket_.async_send_to(
				boost::asio::buffer(*message), *ep,
				boost::bind(&udp_server::handle_send, this,
						ep,
					    message,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred));
			start_receive();
		}
	}

	void handle_send(
			 boost::shared_ptr<udp::endpoint> ep,
			 boost::shared_ptr<std::string> message/*message*/,
			 const boost::system::error_code & /*error*/,
			 std::size_t /*bytes_transferred*/)
	{
		printf("out = %s\n",message->c_str());
	}

	udp::socket socket_;
	boost::array<char, 1> recv_buffer_;
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