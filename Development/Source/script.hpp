#pragma once

#include "script_event.hpp"
#include "script_action.hpp"

class Script
{
public:
	Script();

	void addLine(shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action);
	void removeLine(int lineNumber);

	void execute();

private:
	vector<std::pair<shared_ptr<ScriptEvent>, shared_ptr<ScriptAction>>> _scriptLines;
};