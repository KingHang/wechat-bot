#pragma once
#include <Windows.h>
#include <unordered_map>


namespace arris {
namespace wechat {
	template<typename T>
	class mgr {
	public:
		mgr() {}
		~mgr() {
			typename std::unordered_map<int, T*>::iterator  iter = obj_map_.begin();
			for (; iter != obj_map_.end(); iter++) {
				if ((*iter).second != nullptr) {//first key,second value
					try {
						delete (*iter).second;//free pointer
						(*iter).second = nullptr;
					}
					catch (...) {
						__OutputDebugString(TEXT("mgr error:free pointer\n"));
					}
				}
			}
		}
		void run(const int type,const wx_msg& st_msg) {
			if (exist(type) == false) {
				return;
			}
			try{
				obj_map_[type]->handle_msg(st_msg);
			}
			catch (...) {
				__OutputDebugString(TEXT("type no error:%d\n"),type);
			}
		}
		void add(int type, T* p) {
			obj_map_.insert(std::make_pair(type, p));
		}
		//void set_data(const wx_msg& st_msg) {
		//	st_msg_ = st_msg;
		//}
	private:
		bool exist(int type) {
			bool is_exist = true;
			size_t n = obj_map_.count(type);

			if (n == 0) {
				is_exist = false;
			}
			return is_exist;
		}
		
	private:
		std::unordered_map<int, T*> obj_map_;
		//wx_msg st_msg_;
	};//class mgr

	//using mgr_ptr = std::unique_ptr<mgr<T>>();
}//
}//