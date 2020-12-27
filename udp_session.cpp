#include "udp_session.h"
#include <boost/smart_ptr.hpp>

int UDP_SESSION::session_id = 0;

boost::shared_ptr<std::string> make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return boost::make_shared<std::string>(ctime(&now));
}

void UDP_SESSION::handle_receive(boost::shared_ptr<UDP_SESSION> udp,
				 const boost::system::error_code &error,
				 std::size_t /*bytes_transferred*/
)
{
	if (!error) {
		printf("receive %s\n", recv_buffer.c_array());

		auto p = make_daytime_string();
		int len = snprintf(snd_buffer.c_array(),2048 ,"test\n");
		_socket.async_send_to(
			boost::asio::buffer(snd_buffer, len), ep,
			boost::bind(&UDP_SESSION::handle_transmit, this,
				    udp,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
	} else {
		start_new_receive(_socket);
	}
}

void UDP_SESSION::handle_transmit(boost::shared_ptr<UDP_SESSION> udp,
				  const boost::system::error_code &error,
				  std::size_t num/*bytes_transferred*/
)
{
	printf("send len = %d ok\n",num);
	//end sssion && need new receive
	start_new_receive(_socket);
}
