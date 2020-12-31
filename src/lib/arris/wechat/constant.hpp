#include <queue>
#include <vector>
#include <string>

namespace arris {
namespace net {

	//default websocket port
	const unsigned int kPort = 5555;

	enum MsgType {
		kHook = 0,
		kSend = 1
	};

	enum LogType {

	};


	struct MsgContent {
		int msgid;
		unsigned int type;
		std::wstring start_time;
		std::wstring end_time;
		std::wstring unique_id;//wx id ,chatroom id
		std::wstring sender;
		std::wstring receiver;
		std::wstring content;

	};

	
	//
	std::queue<MsgContent> kMsgQueue;

}//namespace net
}//namespace arris