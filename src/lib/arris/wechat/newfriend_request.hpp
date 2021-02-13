#pragma once

#include <Windows.h>
#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/msgtoqueue.hpp>
#include <arris/wechat/constant.hpp>

namespace arris {

namespace wechat {
class newfriend_request :public iwxbase {
public:
	newfriend_request(DWORD eax) :eax_(eax) {
		type_ = static_cast<int>(MsgType::kHookTxtMsgType);
		msgtoqueue_ = std::make_unique<msgtoqueue>();
	}
private:
	DWORD eax_;
	int type_;
	msgtoqueue_ptr msgtoqueue_;

};

}//namespace wecaht
}//namespace arris