#ifndef __dummy_client_h____
#define __dummy_client_h____
#include "iot_client_session.h"

class DUMMY_CLIENT : public IOT_BASE {
    public:
	DUMMY_CLIENT(
		boost::asio::io_service &in_io_svc, boost::asio::ip::address addr, int port, uint64_t insn)
		: IOT_BASE(in_io_svc, addr, port), sn(insn)
	{
		start();
	}

    private:
	void start();
	int make_login_session();
	void decode_login_session(size_t sz);
	boost::array<char, 2048> recv_buffer;
	boost::array<char, 2048> snd_buffer;

	uint64_t type_id = 0x3;
	uint64_t sn;

	int cmd;
	int index;
	uint32_t session_id;
};

#endif
