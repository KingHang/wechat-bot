#pragma once

#include <string>
#include <memory>
#include <functional>
#include <arris/wechat/constant.hpp>
#include <arris/thread/wxthread.hpp>

using namespace arris::thread;
using arris::wechat::kMsgQueue;
namespace arris {
namespace wechat {

class msgtoqueue {
public:
	msgtoqueue() {}
	~msgtoqueue() {}

	void push(const std::string& msg) {
		kMsgQueue.push(msg);
	}
	void send_to_queue(const std::string& msg) {
		auto p = thread_pool.enqueue(std::bind(&msgtoqueue::push, this, msg));
		p.get();
	}

};//class msgtoqueue

}//namespace wechat
}//namespace arris