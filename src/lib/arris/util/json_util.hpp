#pragma once
#include <nlohmann/json.hpp>
#include <arris/util/log_util.hpp>
#include <arris/util/str_util.hpp>
#include <arris/util/utf8.hpp>
#include <arris/wechat/wxbase.hpp>
#include <arris/wechat/constant.hpp>
//using namespace arris::net;
using nlohmann::json;
using namespace arris::util;
using namespace arris::wechat;


namespace arris {
namespace util {

class tinyjson {
public:
	tinyjson() {}

	bool is_json(const std::string& str) {
		__OutputDebugString(TEXT("is json string:%s\n"),str.c_str());
		bool is_json_type = true;
		try {
			json_obj_ = nlohmann::json::parse(str);
		}
		catch (json::exception& e) {
			std::wstring str = string_to_wstring(e.what());
			__OutputDebugString(TEXT("error:%s\n"), str.c_str());
			is_json_type = false;
		}
		return is_json_type;
	}

	std::string ret_msg(const std::string& id,const std::string &status,const std::string content,int type) {
		json j;
		j["id"] = id;
		j["sender"] = kServerSide;
		j["receiver"] = kClientSide;
		j["status"] = status;
		j["content"] = content;
		j["time"] = s_wxtime();
		j["type"] = type;
		j["srvid"] = MsgType::kServerSideMsg;

		std::string dump_str = j.dump();
		return dump_str;
	}
	

	json parser(const std::string& str) {
		//std::wstring wstr = string_to_wstring(str);
		json j;
		try {
			j = nlohmann::json::parse(str);
		}
		catch (json::exception& e) {
			__OutputDebugString(TEXT("error:%s\n"), e.what());
		}
		return j;
	}

	int get_type(const std::string& str) {
		json j = parser(str);
		return j["type"];
	}

	wx_msg get_st(const std::string &str) {
		wx_msg st;
		json j = parser(str);
		st.id = j["id"];
		std::string s_wxid = j["wxid"];
		std::string s_content = j["content"];

		st.wxid = utf8_to_ucs2(string_to_char(s_wxid));
		st.content = utf8_to_ucs2(string_to_char(s_content));

		return st;
	}
protected:
	json opr() {
	}
	
private:
	json json_obj_;
};// class tinyjson

using tinyjson_ptr = std::unique_ptr<tinyjson>;

}//namespace util
}//namespace arris