#pragma once

#include <thread.hpp>
#include <queue.hpp>
#include <ticks.hpp>

#include "Fifo.hpp"

namespace rtos = cpp_freertos;

namespace tasks {

namespace base {

template<const char* U, class T, uint32_t N>
class TaskBase : public rtos::Thread
{
public:
	using MsgType = T;
	static constexpr uint32_t FIFO_SIZE = N;
	using FifoType = Fifo<MsgType, FIFO_SIZE>;

	static void fifo_flush()
	{
		return _input_fifo.Flush();
	}

	static bool fifo_is_empty()
	{
		return _input_fifo.IsEmpty();
	}

	static bool fifo_push(MsgType* message)
	{
		return _input_fifo.Enqueue(message);
	}

	static bool fifo_push(MsgType* message, TickType_t timeout)
	{
		return _input_fifo.Enqueue(message, timeout);
	}


	static void fifo_push_from_isr(MsgType* message)
	{
		BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
		_input_fifo.EnqueueFromISR(message, &pxHigherPriorityTaskWoken);
	}

	TaskBase(uint16_t StackDepth, UBaseType_t Priority) :
		Thread(U, StackDepth, Priority){};
	virtual ~TaskBase() = default;

protected:
	MsgType _fifo_data;

	void _blocking_read() {
		_input_fifo.Dequeue(&_fifo_data, portMAX_DELAY);
	}

	bool _read(uint32_t timeout_ms) {
		TickType_t timeout =
					rtos::Ticks::MsToTicks(timeout_ms);

		return _input_fifo.Dequeue(&_fifo_data, timeout);
	}

	static FifoType _input_fifo;

	virtual void Run() = 0;
};

template<const char* U, class T, uint32_t N>
typename TaskBase<U, T, N>::FifoType TaskBase<U, T, N>::_input_fifo;

}

}


