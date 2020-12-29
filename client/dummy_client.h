#ifndef __dummy_client_h____
#define __dummy_client_h____
#include "iot_client_session.h"

class DUMMY_CLIENT : public IOT_BASE {
    public:
	DUMMY_CLIENT(
		boost::asio::io_service &in_io_svc, boost::asio::ip::address addr, int port, uint64_t insn)
		: IOT_BASE(in_io_svc, addr, port), sn(insn)
	{
		init_svc();
	}

    private:
	void init_svc();

	void handle_receive(
		const boost::system::error_code &error,
		std::size_t /*bytes_transferred*/
	);

	void handle_transmit(
		const boost::system::error_code &error,
		std::size_t /*bytes_transferred*/
	);

	void wait_end(const boost::system::error_code &ec);

	boost::array<char, 2048> recv_buffer;
	boost::array<char, 2048> snd_buffer;

	uint64_t type_id = 0x3;
	uint64_t sn;

	int cmd;
	int index;
	uint32_t session_id;
};

#endif
