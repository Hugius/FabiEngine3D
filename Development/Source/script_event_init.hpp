#pragma once

#include "script_event.hpp"

class ScriptEventInit : public ScriptEvent
{
public:
	using ScriptEvent::ScriptEvent;

	bool isTriggered() override;
	void reset() override;

private:
	bool _isAlreadyTriggered = false;
};