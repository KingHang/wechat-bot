#pragma once
#include <memory>
namespace arris {
namespace net {
class inet {
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual ~inet() {}
};

using inet_ptr = std::unique_ptr<inet>;

//template<typename T>
class netfactory{
public:
	virtual inet_ptr create() = 0;
	virtual ~netfactory() {}
};

template<typename T, typename Q>
class netcreate :public netfactory<T> {
public:
	~netcreate() {}
	virtual inet_ptr create() {
		return std::make_unique<Q>();
	}
};

}//namespace net
}//namespace arris