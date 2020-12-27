#include "udp_session.h"
#include <boost/smart_ptr.hpp>

int UDP_SESSION::session_id = 0;

boost::shared_ptr<std::string> make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return boost::make_shared<std::string>(ctime(&now));
}

void UDP_SESSION::handle_receive(
	const boost::system::error_code &error,
	std::size_t /*bytes_transferred*/
)
{
	if (!error) {
		printf("session = %d , receive %s\n", this_session_id, recv_buffer.c_array());

		auto p = make_daytime_string();
		int len = snprintf(snd_buffer.c_array(), 2048, "test\n");
		socket.async_send_to(
			boost::asio::buffer(snd_buffer, len), ep,
			boost::bind(&UDP_SESSION::handle_transmit, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
	} else {
		start_receive();
	}
}

void UDP_SESSION::handle_transmit(
	const boost::system::error_code &error,
	std::size_t num /*bytes_transferred*/
)
{
	printf("session = %d , send len = %lu ok\n", this_session_id, num);
	start_receive();
}
