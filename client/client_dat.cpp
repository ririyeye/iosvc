#include "client_dat.h"
#include <string.h>
#include <arpa/inet.h>
#include <algorithm>
#include "crc16.h"

void TLV_PKG::add_tlv(int tag, void *src, int len)
{
	TLV_NODE nd;
	nd.tag = tag;
	nd.tlvdat.resize(len);
	memcpy(&nd.tlvdat[0], src, len);

	dat.emplace_back(nd);
}

std::shared_ptr<std::vector<char> > TLV_PKG::Transfer2dat(uint16_t cmd, uint32_t index, uint32_t session_id)
{
	const int header_offset = 12;
	int maxlen = 0 + header_offset;
	for (auto &nod : dat) {
		maxlen += 4;
		maxlen += nod.tlvdat.size();
	}

	std::shared_ptr<std::vector<char> > ret = std::make_shared<std::vector<char>>();
	ret->resize(maxlen);

	int offset = 0 + header_offset;
	char *pos0 = &ret->at(0);

	for (auto &nod : dat) {
		uint16_t tag = htons(nod.tag);
		uint16_t len = htons(nod.tlvdat.size());
		memcpy(pos0 + offset + 0, &tag, 2);
		memcpy(pos0 + offset + 2, &len, 2);
		std::reverse_copy(nod.tlvdat.begin(), nod.tlvdat.end(), pos0 + offset + 4);

		offset += 4;
		offset += nod.tlvdat.size();
	}

	offset = 2;
	cmd = htons(cmd);
	memcpy(pos0 + offset, &cmd, 2);

	offset += 2;
	index = htonl(index);
	memcpy(pos0 + offset, &index, 4);

	offset += 4;
	session_id = htonl(session_id);
	memcpy(pos0 + offset, &session_id, 4);

	uint16_t crc = crc_16(pos0 + 2, maxlen - 2, 1);
	crc = htons(crc);
	memcpy(pos0, &crc, 2);

	return ret;
}