#ifndef __CLIENT_DAT_H____
#define __CLIENT_DAT_H____

#include <stdint.h>
#include <vector>
#include <memory>

struct TLV_PKG {
    public:
	void add_tlv(int tag, void *dat, int len);
	std::shared_ptr<std::vector<char> > Transfer2dat(uint16_t cmd, uint32_t index, uint32_t session_id);

    private:
	struct TLV_NODE {
		int tag;
		std::vector<unsigned char> tlvdat;
	};
	std::vector<TLV_NODE> dat;
};

#endif
