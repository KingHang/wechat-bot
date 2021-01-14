#pragma once
#include <Windows.h>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <arris/wechat/wxbase.hpp>
#include <arris/util/log_util.hpp>
#include <arris/util/str_util.hpp>
#include <arris/util/read_mem.hpp>
#include <arris/wechat/msgtoqueue.hpp>
#include <arris/util/json_util.hpp>
#include <arris/wechat/offset_version.hpp>
using nlohmann::json;
using namespace arris::util;
using namespace arris::wechat;

namespace arris {
	namespace wechat {
		class txtmsg_hook :public iwxbase {
		public:
			txtmsg_hook(DWORD eax):eax_(eax) {
				type_ = static_cast<int>(MsgType::kHookTxtMsgType);
				msgtoqueue_ = std::make_unique<msgtoqueue>();
			}
			~txtmsg_hook() {}
			virtual int get_type() {
				return type_;
			};
			virtual void handle_msg() {
				std::string msg = to_string();
				__OutputDebugString(TEXT("msg:%s\n"),msg.c_str());
				msgtoqueue_->send_to_queue(msg);
			};

		private:
			std::string to_string() {
				json j;
				j["id"] = time2id();
				j["type"] = type_;
				j["wxid"] = ucs2_to_utf8(wstring_to_wchar(get_wxid()));
				j["content"] = ucs2_to_utf8(wstring_to_wchar(get_txtmsg()));
				std::wstring c = get_txtmsg();
				__OutputDebugString(TEXT("content:%s\n"),c.c_str());
				j["time"] = s_wxtime();
				j["srvid"] = MsgType::kServerSideMsg;
				j["receiver"] = "future";//接收者微信id
				j["sender"] = "future";//发送方微信id
				std::string result;
				try {
					result = j.dump();
				}
				catch (json::exception& e) {
					tinyjson tiny;
					result = tiny.ret_msg(time2id(), kMsgFailedStatus, e.what(), type_);
				}
				return result;
			}
			std::wstring get_txtmsg() {
				DWORD size_addr = static_cast<DWORD>(version::hook_txtmsg_offset::msg_content_offset) + 0x4;
				DWORD wxid_addr = static_cast<DWORD>(version::hook_txtmsg_offset::msg_content_offset);
				__OutputDebugString(TEXT("size addr:%x\n"),size_addr);
				__OutputDebugString(TEXT("wxid_addr addr:%x\n"), wxid_addr);

				std::wstring content = getwstr_from_addr(eax_, size_addr, wxid_addr);
				return content;
			}
			std::wstring get_wxid() {
				DWORD size_addr = eax_+ static_cast<DWORD>(version::hook_txtmsg_offset::wxid_offset)+0x4;
				DWORD wxid_addr = eax_+ static_cast<DWORD>(version::hook_txtmsg_offset::wxid_offset);
				std::wstring wxid = getwstr_from_addr(eax_, size_addr, wxid_addr);
				return wxid;
			}
		private:
			DWORD eax_;
			int type_;
			msgtoqueue_ptr msgtoqueue_;
		};


}
}