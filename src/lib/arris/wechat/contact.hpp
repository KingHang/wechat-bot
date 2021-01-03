#pragma once

#include <arris/wechat/wxbase.hpp>

namespace arris {
namespace wechat {
class contact :public iwxbase {
public:
	~contact() {}
	virtual void handle_msg() {
	}
	virtual int get_type() {
		return type_;
	}
private:
	int type_;
};
}//namespace wechat
}//namespace arris