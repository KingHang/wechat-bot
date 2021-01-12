#pragma once

namespace arris {
	namespace wechat {
		class version {//3.1.0.66
		public:
			enum class contact_data_offset
			{
				contact_offset = 0x1886B38,
				contact_addr_offset = 0xB4,
				wxid_sign   = 0x14,
				wxid1_offset = 0x10,
				wxid1_len = 0x20,
				wxid2_offset = 0x30,
				wxid2_len    = 0x34,
				wxcode_offset = 0x44,
				wxnick_offset = 0x8c,
				wxnick_len = 0x90
			};
		};
	}
}