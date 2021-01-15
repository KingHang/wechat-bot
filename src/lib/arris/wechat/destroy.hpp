#pragma once
#include <Windows.h>
#include <arris/wechat/constant.hpp>
#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/abnormalmsg.hpp>

using namespace arris::wechat;
namespace arris {
namespace wechat {

class dll_destroy:public iwxbase {
public:
	dll_destroy() {
		type_ = static_cast<int>(MsgType::kDestroyDllWin);
	}
	~dll_destroy() {}
	void desroy_win() {
		HWND h_wnd = ::FindWindow(NULL, TEXT("wechatbot55555"));
		if (h_wnd == NULL)
		{
			std::string content = "the handle is null";
			abnormal_msg msg;
			msg.handled_msg(content);
		}
		else {
			__OutputDebugString(TEXT("handle is :%x\n"),h_wnd);
			::PostMessage(h_wnd, WM_CLOSE, NULL, NULL);
		}
	}
	virtual void handle_msg(const wx_msg& v_st_msg) {
		desroy_win();
	}
	virtual int get_type() {
		return type_;
	}
	virtual void set_data(const wx_msg& msg) {
	};

private:
	int type_;
};// class dll_destroy

}//namespace wechat 
}//namespace arris