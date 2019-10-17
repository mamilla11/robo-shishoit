#include "SystemState.h"

SystemState::Queue SystemState::_events = SystemState::Queue();

uint8_t SystemState::getEventCount() {
	return SystemState::_events.size();
}

SystemState::Event SystemState::popEvent() {
	SystemState::Event event = SystemState::Event::NONE;

	if (SystemState::_events.size() > 0) {
		event = SystemState::_events.front();
		SystemState::_events.pop();
	}

	return event;
}

bool SystemState::pushEvent(SystemState::Event event) {
	if (SystemState::_events.full()) {
		return false;
	}

	SystemState::_events.push(event);
	return true;
}

