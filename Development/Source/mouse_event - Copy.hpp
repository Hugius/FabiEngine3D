#pragma once

#include <string>

using std::string;

enum class EventClass
{
	INIT_EVENT,
	INPUT_EVENT,
	TIME_EVENT,
	COLLISION_EVENT
};

enum class InitEventType
{

};

enum class InputEventType
{

};

enum class TimeEventType
{

};

enum class CollisionEventType
{

};

class ScriptEvent
{
public:
	ScriptEvent(EventType eventType);

	EventType getType();

private:
	EventType _eventType;
};