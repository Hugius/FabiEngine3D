#pragma once

#include "script_event.hpp"
#include "script_action.hpp"

struct ScriptLine
{
	string ID;

	shared_ptr<ScriptEvent> event;
	shared_ptr<ScriptAction> action;
};

class Script
{
public:
	Script();

	void addLine(const string& ID, shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action);
	void removeLine(const string& ID);
	void reset();
	void execute();

	int getLineCount();

	bool isExisting(const string& ID);

	ScriptLine& getScriptLine(const string& ID);

	vector<string> getAllScriptIDs();

private:
	vector<ScriptLine> _scriptLines;
};