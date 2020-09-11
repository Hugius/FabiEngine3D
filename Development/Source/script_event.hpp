#pragma once

#include <string>

using std::string;

enum class ScriptEventType
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
	ScriptEvent(ScriptEventType eventType) :
		_eventType(eventType)
	{

	}

	ScriptEventType getType()
	{
		return _eventType;
	}

private:
	ScriptEventType _eventType;
};