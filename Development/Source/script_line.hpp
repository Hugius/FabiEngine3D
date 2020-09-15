#pragma once

#include "script_event.hpp"
#include "script_action.hpp"

struct ScriptLine
{
	string ID;

	shared_ptr<ScriptEvent> event;
	shared_ptr<ScriptAction> action;
};