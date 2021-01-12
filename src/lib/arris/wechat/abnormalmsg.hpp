#pragma once

#include <string>
#include <memory>

#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/msgtoqueue.hpp>
#include <arris/wechat/constant.hpp>
#include <arris/util/json_util.hpp>

using namespace arris::util;
using namespace arris::wechat;


namespace arris {
	namespace wechat {

		class abnormal_msg {
		public:
			abnormal_msg() {}
			~abnormal_msg() {}
			void handled_msg(const std::string &content) {
				std::string msg = json_->ret_msg(time2id(), kMsgFailedStatus, content, static_cast<int>(MsgType::kAbnormalMsg));
				msgtoqueue_->send_to_queue(msg);
			};

		private:
			std::unique_ptr<tinyjson> json_;
			std::unique_ptr<msgtoqueue> msgtoqueue_;
			//std::string content_;
		};//class abnormal_msg

	}//namespace wechat
}//namespace arris