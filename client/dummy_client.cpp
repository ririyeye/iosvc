#include "dummy_client.h"
#include <iostream>
#include "mycrypto.h"

void DUMMY_CLIENT::init_svc()
{
	unsigned char dat[128];
	int len = crypto_data(snd_buffer.c_array(), dat, sizeof(dat), snd_buffer.max_size());

	if (len <= 0) {
		timer.expires_from_now(boost::posix_time::seconds(5));
		timer.async_wait(boost::bind(&DUMMY_CLIENT::wait_end, this, boost::asio::placeholders::error));
		return;
	}

	udp_socket.async_send_to(
		boost::asio::buffer(snd_buffer, len), udp_ep,
		boost::bind(&DUMMY_CLIENT::handle_transmit, this,
			    boost::asio::placeholders::error,
			    boost::asio::placeholders::bytes_transferred));
}

void DUMMY_CLIENT::wait_end(const boost::system::error_code &ec)
{
	if (!ec) {
		init_svc();
	} else {
		std::cout << ec << std::endl;
		init_svc();
	}
}

void DUMMY_CLIENT::handle_transmit(
	const boost::system::error_code &error,
	std::size_t num /*bytes_transferred*/
)
{
	if (!error) {
		timer.expires_from_now(boost::posix_time::seconds(5));
		timer.async_wait(boost::bind(&DUMMY_CLIENT::wait_end, this, boost::asio::placeholders::error));
	}
}

void DUMMY_CLIENT::handle_receive(
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
