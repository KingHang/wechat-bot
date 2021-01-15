#pragma once
#include <Windows.h>
#include <unordered_map>
#include <arris/wechat/wxbase.hpp>
#include <arris/util/log_util.hpp>
#include <arris/wechat/offset_version.hpp>
#include <arris/wechat/txtmsg_hook.hpp>
#include <arris/wechat/mgr.hpp>

using namespace arris::util;
using namespace arris::wechat;

namespace arris {
namespace wechat {

class hookmsg_mgr_ex {
public:
	hookmsg_mgr_ex(DWORD eax):eax_(eax) {
		mgr_ptr_ = std::make_unique<mgr<iwxbase>>();
		init();
	}
	void run(int type) {
		mgr_ptr_->run(type);
	}
private:
	void init() {
		p_txtmsg_hook_ = new txtmsg_hook(eax_);
		mgr_ptr_->add(p_txtmsg_hook_->get_type(), p_txtmsg_hook_);
	}
private:
	DWORD eax_;
	std::unique_ptr<mgr<iwxbase>> mgr_ptr_;
	iwxbase* p_txtmsg_hook_;

};
/*
class hookmsg_mgr {
public:
	hookmsg_mgr(DWORD eax):eax_(eax) {
		init();
	}
	~hookmsg_mgr() {
		if (p_txtmsg_hook_ != nullptr) {
			delete p_txtmsg_hook_;
			p_txtmsg_hook_ = nullptr;
		}
	}
	
	void run(int type) {
		__OutputDebugString(TEXT("run type:%d\n"),type);
		if (exist(type) == false) {
			return;
		}
		obj_map_[type]->handle_msg();
	}
private:
	bool exist(int type) {
		bool is_exist = true;
		size_t n = obj_map_.count(type);
		__OutputDebugString(TEXT("type count:%d\n"),n);
		if (n == 0) {
			is_exist = false;
		}
		return is_exist;
	}
	void init() {

		p_txtmsg_hook_ = new txtmsg_hook(eax_);
		add(p_txtmsg_hook_->get_type(), p_txtmsg_hook_);
	}
	void add(int type, iwxbase* p) {
		obj_map_.insert(std::make_pair(type, p));
	}
private:
	DWORD eax_;
	std::unordered_map<int, iwxbase*> obj_map_;
	iwxbase* p_txtmsg_hook_;
};//class hookmsg*/
		
}//namespace wechat
}//namespace arris