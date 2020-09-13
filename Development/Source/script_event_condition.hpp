#pragma once

#include "script_event.hpp"

class ScriptEventCondition : public ScriptEvent
{
public:
	using ScriptEvent::ScriptEvent;

	bool isTriggered() override;

private:

};