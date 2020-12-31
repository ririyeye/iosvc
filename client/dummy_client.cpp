#include "dummy_client.h"
#include <iostream>
#include "mycrypto.h"
#include "client_dat.h"
#include <boost/format.hpp>
#include <boost/asio/io_context_strand.hpp>

void testa(int b){
	printf("123 = %d\n",b);

}
void DUMMY_CLIENT::start()
{
	boost::asio::spawn(strand.context(), [this](boost::asio::yield_context yield) {
		try {
			if(!udp_socket.is_open())
				udp_socket.open(boost::asio::ip::udp::v4());

			int len = make_login_session();
			if (len <= 0) {
				timer.expires_from_now(std::chrono::seconds(5));
				return;
			}

			udp_socket.async_send_to(
				boost::asio::buffer(snd_buffer, len), udp_ep, yield);

			timer.expires_from_now(std::chrono::seconds(5));

			int recsz = udp_socket.async_receive_from(
				boost::asio::buffer(recv_buffer), udp_ep, yield);

			if (recsz > 0)
				decode_login_session(recsz);
		} catch (std::exception &exp) {
			std::cout << "123"<< exp.what() << std::endl;
		}
		timer.cancel();
		boost::system::error_code ignored_ec;
		udp_socket.close(ignored_ec);
	});

	boost::asio::spawn(strand.context(), [this](boost::asio::yield_context yield) {
		boost::system::error_code ignored_ec;
		while (udp_socket.is_open()) {
			timer.async_wait(yield[ignored_ec]);
			if (timer.expires_from_now() <= std::chrono::seconds(0)) {
				udp_socket.close(ignored_ec);
			}
		}		
		strand.post(boost::bind(&DUMMY_CLIENT::start,this));
	});
}

int DUMMY_CLIENT::make_login_session()
{
	TLV_PKG tlv;
	//登录 无密钥
	cmd = 2;
	index = 0;
	session_id = 0;

	tlv.add_rev_tlv(255, &sn, sizeof(sn));

	auto dat = tlv.Transfer2dat(cmd, index, session_id);
	int len = encrypto_data(snd_buffer.c_array(), &dat->at(0), dat->size(), snd_buffer.max_size(), session_id, sn);
	return len;
}

void DUMMY_CLIENT::decode_login_session(
	std::size_t sz /*bytes_transferred*/
)
{
	static int session_id = 0;

	printf("get from server %d,%lu\n", session_id++, sz);
	timer.cancel();

	auto p = TLV_PKG::GenFrombytes(recv_buffer.c_array(), sz);
	if (!p) {
		printf("no tlv\n");
	}

	std::cout << boost::format("cmd = %1% , index %2% session_id %3%") % p->cmd % p->index % p->session_id;
	for (auto &nd : p->dat) {
		std::cout << boost::format("\n	tag %1%,len %2%") % nd.tag % nd.tlvdat.size();
	}

	std::cout << std::endl;
}
