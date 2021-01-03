#pragma once

#include <memory>
namespace arris {
namespace wechat {

class iwxbase {
public:
	virtual ~iwxbase() {}
	virtual void handle_msg() = 0;
	virtual int get_type() = 0;
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