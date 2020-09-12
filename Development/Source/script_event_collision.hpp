#pragma once

#include "script_event.hpp"

class ScriptEventCollision : public ScriptEvent
{
public:
	using ScriptEvent::ScriptEvent;

	bool isTriggered() override;

private:
	
};