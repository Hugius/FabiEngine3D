#pragma once

#include "fabi_engine_3d.hpp"

enum class ScriptEventType
{
	INIT_EVENT,
	INPUT_EVENT,
	COLLISION_EVENT,
	TIME_EVENT,
	CONDITION_EVENT
};

class ScriptEvent
{
public:
	ScriptEvent(FabiEngine3D& fe3d, ScriptEventType eventType);

	virtual bool isTriggered() = 0;
	virtual void reset()
	{

	}

	const ScriptEventType getType();

protected:
	FabiEngine3D& _fe3d;

private:
	const ScriptEventType _eventType;
};