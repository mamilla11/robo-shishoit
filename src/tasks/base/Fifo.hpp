#pragma once

#include <queue.hpp>

namespace rtos = cpp_freertos;

namespace tasks {

namespace base {

template<class T, uint32_t N>
class Fifo : public rtos::Queue
{
public:
	using FifoType = T;
	static constexpr uint32_t ITEMS_COUNT = N;

	Fifo() :
		Queue(N, sizeof(T))
	{ }

	virtual ~Fifo() = default;
};

}

}

