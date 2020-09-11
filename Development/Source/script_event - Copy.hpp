#pragma once

#include <string>

using std::string;

enum class EventType
{
	INIT_EVENT,
	KEYBOARD_EVENT,
	MOUSE_EVENT,
	TIME_EVENT,
	COLLISION_EVENT
};

class ScriptEvent
{
public:
	ScriptEvent(EventType eventType);

	EventType getType();

private:
	EventType _eventType;
};