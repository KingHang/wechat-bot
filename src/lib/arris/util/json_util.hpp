#include <nlohmann/json.hpp>
#include <arris/util/log_util.hpp>
#include <arris/util/str_util.hpp>

#include <arris/wechat/constant.hpp>
using namespace arris::net;
using nlohmann::json;
using namespace arris::util;


namespace arris {
namespace util {
class structtojson {
public:
	json tojson() {
		json j;
		//j[] = "";
	}
};

class tinyjson {
public:
	tinyjson() {}
	json parser(std::string& str) {
		json j;
		try {
			j = nlohmann::json::parse(str);
		}
		catch (json::exception& e) {
			std::cout << e.what() << std::endl;
		}
		return j;
	}
protected:
	json opr() {
	}
	bool is_json(std::string& str) {
		bool is_json_type = true;
		try {
			auto t = nlohmann::json::parse(str);
		}
		catch (json::exception& e) {
			std::wstring str = string_to_wstring(e.what());
			__OutputDebugString(TEXT("error:%s\n"), str.c_str());
			is_json_type = false;
		}
		return is_json_type;
	}
private:
};// class tinyjson
}//namespace util
}//namespace arris