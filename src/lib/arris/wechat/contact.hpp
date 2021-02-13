#pragma once
#include <memory>
#include <arris/wechat/constant.hpp>
#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/msgtoqueue.hpp>
#include <arris/wechat/contact_tree.hpp>
using namespace arris::wechat;

namespace arris {
namespace wechat {
class contact :public iwxbase {
public:
	contact() {
		type_ = static_cast<int>(MsgType::kUserListFromContact);
		contact_tree_ = std::make_unique<contact_tree>();
		msgtoqueue_ = std::make_unique<msgtoqueue>();
	}
	~contact() {}
	virtual void handle_msg(const wx_msg& v_st_msg) {
		DWORD node = contact_tree_->node();
		contact_tree_->list_clear();
		contact_tree_->recurse(node);
		std::string msg = contact_tree_->to_string("test id 202222",type_);
		msgtoqueue_->send_to_queue(msg);
	}
	virtual int get_type() {
		return type_;
	}
	//virtual void set_data(const wx_msg& msg) {};

private:
	int type_;
	contact_tree_ptr contact_tree_;
	msgtoqueue_ptr msgtoqueue_;
};
}//namespace wechat
}//namespace arris