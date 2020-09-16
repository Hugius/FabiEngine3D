#pragma once

#include "fabi_engine_3d.hpp"

enum class ScriptEventType
{
	INITIALIZATION,
	INPUT,
	COLLISION,
	TIME,
	CONDITION,
	NONE
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