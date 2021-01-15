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

			enum class hook_common_offset {
				hook_point_offset = 0x3C9C32,
				call_offset = 0x85A30
			};
			enum class hook_msg_type {
				hook_msg_type_offset = 0x30
			};
			enum class hook_txtmsg_offset {
				wxid_offset = 0x40,
				msg_content_offset = 0x68,
				group_msg_sender_offset = 0x144
			};

			enum class send_txtmsg_offset {
				send_call_addr = 0x3A0C20,

			};
		};
	}
}