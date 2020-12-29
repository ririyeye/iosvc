#ifndef __CLIENT_DAT_H____
#define __CLIENT_DAT_H____

#include <stdint.h>
#include <vector>
#include <memory>

struct TLV_PKG {
    public:
	void add_rev_tlv(int tag, void *src, int len);
	void add_tlv(int tag, void *src, int len);

	std::shared_ptr<std::vector<char> > Transfer2dat(uint16_t cmd, uint32_t index, uint32_t session_id);
	static std::shared_ptr<TLV_PKG> GenFrombytes(char *dat, size_t len);

	int cmd;
	uint16_t session_id;
	uint16_t index;

	struct TLV_NODE {
		int tag;
		std::vector<unsigned char> tlvdat;
	};
	std::vector<TLV_NODE> dat;
};

#endif
