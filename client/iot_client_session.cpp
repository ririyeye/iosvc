#include "iot_client_session.h"
#include <iostream>

void IOT_BASE::init_svc()
{
	int len = snprintf(snd_buffer.c_array(), snd_buffer.max_size(), "test\n");
	udp_socket.async_send_to(
		boost::asio::buffer(snd_buffer, len), udp_ep,
		boost::bind(&IOT_BASE::handle_transmit, this,
			    boost::asio::placeholders::error,
			    boost::asio::placeholders::bytes_transferred));
}

void IOT_BASE::wait_end(const boost::system::error_code &ec)
{
	std::cout << ec << std::endl;
	init_svc();
}

void IOT_BASE::handle_transmit(
	const boost::system::error_code &error,
	std::size_t num /*bytes_transferred*/
)
{
	if (!error) {
		timer.expires_from_now(boost::posix_time::seconds(5));
		timer.async_wait(boost::bind(&IOT_BASE::wait_end, this, boost::asio::placeholders::error));
	}
}

void IOT_BASE::handle_receive(
	const boost::system::error_code &error,
	std::size_t /*bytes_transferred*/
)
{
	// if (!error) {
	// 	printf("session = %d , receive %s\n", this_session_id, recv_buffer.c_array());

	// 	auto p = make_daytime_string();
	// 	int len = snprintf(snd_buffer.c_array(), 2048, "test\n");
	// 	socket.async_send_to(
	// 		boost::asio::buffer(snd_buffer, len), ep,
	// 		boost::bind(&UDP_SESSION::handle_transmit, this,
	// 			    boost::asio::placeholders::error,
	// 			    boost::asio::placeholders::bytes_transferred));
	// } else {
	// 	start_receive();
	// }
}
