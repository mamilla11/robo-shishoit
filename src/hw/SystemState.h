#pragma once

#include <etl/queue.h>

class SystemState {
public:
	SystemState() = default;
	~SystemState() = default;

	enum class Event {
		TOUCH_PRESSED,
		LEFT_BUTTON_LONG_PRESS,
		LEFT_BUTTON_PRESSED,
		RIGHT_BUTTON_PRESSED,
		UPDATE_TIME,
		NONE
	};

	using Queue = etl::queue<Event, 20, etl::memory_model::MEMORY_MODEL_SMALL>;

	static Queue _events;

	static uint8_t getEventCount();
	static Event popEvent();
	static bool pushEvent(Event event);
};
