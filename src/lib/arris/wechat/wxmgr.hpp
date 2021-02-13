#pragma once
#include <unordered_map>
#include <arris/wechat/constant.hpp>
#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/contact.hpp>
#include <arris/wechat/destroy.hpp>
#include <arris/wechat/sendtxtmsg.hpp>
#include <arris/wechat/mgr.hpp>
#include <arris/wechat/personal_info.hpp>
#include <arris/wechat/chatroom.hpp>
#include <arris/wechat/sendpic.hpp>
#include <arris/wechat/room_nick.hpp>
using namespace arris::wechat;
namespace arris {
	namespace wechat {
		class msg_mgr {
		public:
			msg_mgr(){
				mgr_ptr_ = std::make_unique<mgr<iwxbase>>();
				init();
			}
			void run(const int type, const wx_msg& st_msg) {
				mgr_ptr_->run(type,st_msg);
			}
		private:
			void init() {
				p_dll_destroy_ = new dll_destroy();
				mgr_ptr_->add(p_dll_destroy_->get_type(), p_dll_destroy_);

				p_contact_ = new contact();
				mgr_ptr_->add(p_contact_->get_type(), p_contact_);

				p_sendtxtmsg_ = new send_txt_msg();
				mgr_ptr_->add(p_sendtxtmsg_->get_type(), p_sendtxtmsg_);

				p_personal_info_ = new personal_info();
				mgr_ptr_->add(p_personal_info_->get_type(), p_personal_info_);

				p_chatroom_ = new chatroom();
				mgr_ptr_->add(p_chatroom_->get_type(), p_chatroom_);

				p_sendpic_ = new send_pic();
				mgr_ptr_->add(p_sendpic_->get_type(), p_sendpic_);

				p_room_nick_ = new room_nick();
				mgr_ptr_->add(p_room_nick_->get_type(), p_room_nick_);

				//add others here

				//add others here
			}
		private:
			DWORD eax_;
			std::unique_ptr<mgr<iwxbase>> mgr_ptr_;
			iwxbase* p_dll_destroy_;
			iwxbase* p_contact_;
			iwxbase* p_sendtxtmsg_;
			iwxbase* p_personal_info_;
			iwxbase* p_chatroom_;
			iwxbase* p_sendpic_;
			iwxbase* p_room_nick_;

		};

		/*
		class msg_mgr {
		public:
			msg_mgr() {
				init();
			}
			~msg_mgr() {
				if (p_dll_destroy_ != nullptr) {
					delete p_dll_destroy_;
					p_dll_destroy_ = nullptr;
				}
				if (p_contact_!=nullptr) {
					delete p_contact_;
					p_contact_ = nullptr;
				}


			}
			void init() {

				p_dll_destroy_ =new dll_destroy();
				add(p_dll_destroy_->get_type(), p_dll_destroy_);

				p_contact_ = new contact();
				add(p_contact_->get_type(), p_contact_);

			}
			void add(int type, iwxbase* p) {
				obj_map_.insert(std::make_pair(type, p));
			}
			void run(int type) {
				obj_map_[type]->handle_msg();
			}

			bool exist(int type) {
				bool is_exist = true;
				size_t n = obj_map_.count(type);
				if (n == 0) {
					is_exist = false;
				}
				return is_exist;
			}
		private:
			std::unordered_map<int, iwxbase*> obj_map_;
			iwxbase* p_dll_destroy_;
			iwxbase* p_contact_;

		};// msg_mgr*/

	}//namespace wechat
}//namespace arris