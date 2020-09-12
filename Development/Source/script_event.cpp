#include "script_event.hpp"

ScriptEvent::ScriptEvent(FabiEngine3D& fe3d, ScriptEventType eventType) :
	_fe3d(fe3d),
	_eventType(eventType)
{

}

const ScriptEventType ScriptEvent::getType()
{
	return _eventType;
}