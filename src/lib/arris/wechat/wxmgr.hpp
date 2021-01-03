#pragma once
#include <unordered_map>
#include <arris/wechat/constant.hpp>
#include <arris/wechat/wxbase.hpp>

#include <arris/wechat/destroy.hpp>
using namespace arris::wechat;
namespace arris {
	namespace wechat {

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

			}
			void init() {

				p_dll_destroy_ =new dll_destroy();
				add(p_dll_destroy_->get_type(), p_dll_destroy_);

			}
			void add(int type, iwxbase* p) {
				obj_map_.insert(std::make_pair(type, p));
			}
			void run(int type) {
				obj_map_[type]->handle_msg();
				//obj_map_[type]->
				//obj_map_[type]->handle_msg();
				
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
		};// msg_mgr

	}//namespace wechat
}//namespace arris