#include "dummy_client.h"
#include <iostream>
#include "mycrypto.h"
#include "client_dat.h"

void DUMMY_CLIENT::init_svc()
{
	TLV_PKG tlv;
	//登录 无密钥
	cmd = 2;
	index = 0;
	session_id = 0;

	tlv.add_rev_tlv(255, &sn, sizeof(sn));

	auto dat = tlv.Transfer2dat(cmd, index, session_id);
	int len = crypto_data(snd_buffer.c_array(), &dat->at(0), dat->size(), snd_buffer.max_size(), session_id, sn);
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
	}
}

void DUMMY_CLIENT::handle_transmit(
	const boost::system::error_code &error,
	std::size_t num /*bytes_transferred*/
)
{
	if (!error) {
		udp_socket.async_receive_from(
			boost::asio::buffer(recv_buffer), udp_ep,
			boost::bind(&DUMMY_CLIENT::handle_receive, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));

		timer.cancel();
		timer.expires_from_now(boost::posix_time::seconds(1));
		timer.async_wait(boost::bind(&DUMMY_CLIENT::wait_end, this, boost::asio::placeholders::error));
	} else {
		/* code */
	}
}

void DUMMY_CLIENT::handle_receive(
	const boost::system::error_code &error,
	std::size_t sz /*bytes_transferred*/
)
{
	static int session_id = 0;
	if (!error) {
		printf("get from server %d,%lu\n", session_id++, sz);
		timer.cancel();
#if 0
		//timer.expires_from_now(boost::posix_time::seconds(5));
		//timer.async_wait(boost::bind(&DUMMY_CLIENT::wait_end, this, boost::asio::placeholders::error));
#else
		init_svc();
#endif
	}
}
