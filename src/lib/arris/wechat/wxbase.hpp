#pragma once

#include <memory>
namespace arris {
namespace wechat {
struct wxid_st
{
		wchar_t* pstr;
		int len;
		int max_len;
		int temp1 = 0;
		int temp2 = 0;
};
struct wx_msg {
	std::string id;
	std::wstring wxid;
	std::wstring content;
	std::wstring ext;
};
class iwxbase {
public:
	virtual ~iwxbase() {}
	virtual void handle_msg(const wx_msg& v_st_msg) = 0;
	virtual int get_type() = 0;
	//virtual void set_data(const wx_msg& msg) = 0;
};//class iwxbase

using iwxbase_ptr = std::unique_ptr<iwxbase>;
template<typename T>
class wxmsgfactory {
public:
	virtual iwxbase_ptr create() = 0;
	virtual ~wxmsgfactory() {}
};//class wxmsgfactory

template<typename T, typename Q>
class msgconcreate :public wxmsgfactory<T> {
public:
	~msgconcreate() {}
	virtual iwxbase_ptr create() {
		return std::make_unique<Q>();
	}
};//class msgconcreate

}//namespace wechat
}//namespace arris