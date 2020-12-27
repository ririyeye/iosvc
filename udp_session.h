#ifndef __udp_session_h____
#define __udp_session_h____

#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
class UDP_SESSION {
    public:
	UDP_SESSION(boost::asio::ip::udp::socket &insocket)
		: _socket(insocket)
	{
		this_session_id = session_id++;
	}
	boost::array<char, 2048> recv_buffer;
	boost::array<char, 2048> snd_buffer;
	boost::asio::ip::udp::endpoint ep;

	static void start_new_receive(boost::asio::ip::udp::socket &insocket)
	{
		auto session = boost::make_shared<UDP_SESSION> (insocket);
		insocket.async_receive_from(
			boost::asio::buffer(session->recv_buffer), session->ep,
			boost::bind(
				&UDP_SESSION::handle_receive, session.get(), session,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(boost::shared_ptr<UDP_SESSION> udp,
			    const boost::system::error_code &error,
			    std::size_t /*bytes_transferred*/
	);

	void handle_transmit(boost::shared_ptr<UDP_SESSION> udp,
			     const boost::system::error_code &error,
			     std::size_t /*bytes_transferred*/
	);

    private:
	int this_session_id;
	boost::asio::ip::udp::socket &_socket;
	static int session_id;
};

#endif
