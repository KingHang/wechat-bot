#pragma once

#include <arris/wechat/wxbase.hpp>

namespace arris {
namespace wechat {
class contact :public iwxbase {
public:
	~contact() {}
	virtual void handle_msg() {
	}
};
}//namespace wechat
}//namespace arris