#pragma once

namespace arris {
	namespace wechat {
		class version {//3.1.0.66
		public:
			enum class chatroom_member_offset {
				chatroom_addr_offset=0x8c8,//0x840+0x88
				room_id_offset=0x10,
				memberid_list_offset = 0x3c,
				memberid_list_len = 0x4c

			};
			enum class contact_data_offset
			{
				contact_offset = 0x1886B38,//==chatroom_offset
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
				group_msg_sender_offset = 0x164,
				sender_offset1=0x308
			};

			enum class send_txtmsg_offset {
				send_call_addr = 0x3A0C20,

			};
			
			enum class wx_personal_info {
				wx_name_offset = 0x18A35FC,//start address
				wx_code_length_offset = 0x174,
				wx_code_new_version = 0x164,
				wx_code_old_version = 0x41c,
				wx_id_offset = 0x41c,
			};

			enum class send_picmsg_offset {
				call1_offset = 0x574100,
				call2_offset = 0x619c0,
				call3_offset = 0x3a0520
			};
		};
	}
}