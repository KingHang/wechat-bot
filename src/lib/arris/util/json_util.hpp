#pragma once
#include <nlohmann/json.hpp>
#include <arris/util/log_util.hpp>
#include <arris/util/str_util.hpp>
#include <arris/util/utf8.hpp>

#include <arris/wechat/constant.hpp>
using namespace arris::net;
using nlohmann::json;
using namespace arris::util;
using namespace arris::wechat;


namespace arris {
namespace util {

/*
class structtojson {
public:
	json tojson() {
		json j;
	}
};*/

class tinyjson {
public:
	tinyjson() {}

	bool is_json(const std::string& str) {
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
	/*
	std::string st_to_str(const WxMsg& st) {
		json j;
		j["msgid"] = json_obj_["id"];
		j["sender"] = st.sender;
		j["receiver"] = st.receiver;
		j["status"] = st.status;
		j["content"] = st.content;
		j["time"] = s_wxtime();
		j["type"] = json_obj_["type"];
		j["srvid"] = st.srvid;

		std::string dumpstr;
		try {
			dumpstr = j.dump();
		}
		catch (json::exception& e) {
			std::string err = "json dump error!";
			dumpstr = ret_msg(json_obj_["id"], kMsgFailedStatus, err);
		}

		return dumpstr;
	}*/

	json parser(const std::string& str) {
		//std::string ansi_str = U8ToUnicode(str.c_str());
		std::wstring ansi_str = utf8_to_wstring(str);
		__OutputDebugString(TEXT("ansi_str :%s\n"),ansi_str.c_str());
		json j;
		try {

			//__OutputDebugString(TEXT("parser:%s\n"),str.c_str());
			j = nlohmann::json::parse(ansi_str);
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
protected:
	json opr() {
	}
	
private:
	json json_obj_;
};// class tinyjson


}//namespace util
}//namespace arris