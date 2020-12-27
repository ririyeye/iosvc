#ifndef __udp_session_h____
#define __udp_session_h____

#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
class UDP_SESSION {
    public:
	UDP_SESSION(boost::asio::ip::udp::socket &insocket)
		: socket(insocket)
	{
		this_session_id = session_id++;
		start_receive();
	}
	~UDP_SESSION()
	{
		printf("end session %d\n", this_session_id);
	}

	void start_receive()
	{
		socket.async_receive_from(
			boost::asio::buffer(recv_buffer), ep,
			boost::bind(
				&UDP_SESSION::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(
		const boost::system::error_code &error,
		std::size_t /*bytes_transferred*/
	);

	void handle_transmit(
		const boost::system::error_code &error,
		std::size_t /*bytes_transferred*/
	);

    private:
	boost::array<char, 2048> recv_buffer;
	boost::array<char, 2048> snd_buffer;
	boost::asio::ip::udp::endpoint ep;
	int this_session_id;
	boost::asio::ip::udp::socket &socket;
	static int session_id;
};

#endif
