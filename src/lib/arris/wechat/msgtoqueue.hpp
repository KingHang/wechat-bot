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

	/*void __stdcall push(const std::string& msg) {

		kMsgQueue.push(msg);
		__OutputDebugString(TEXT("push queue msg"));
	}

	void __stdcall send_to_queue(const std::string& msg) {
		thread_pool.enqueue(std::bind(&push,msg));
	}*/
class msgtoqueue {
public:
	msgtoqueue() {}
	~msgtoqueue() {}

	void send_to_queue(const std::string& msg) {
		auto p = thread_pool.enqueue(std::bind(&msgtoqueue::push, this, msg));
		//p.get();
	}
private:
	void push(const std::string& msg) {
		kMsgQueue.push(msg);
		//__OutputDebugString(TEXT("push msg:%s\n"),msg.c_str());
	}

};//class msgtoqueue

using msgtoqueue_ptr = std::unique_ptr<msgtoqueue>;
}//namespace wechat
}//namespace arris