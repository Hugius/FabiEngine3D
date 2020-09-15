#pragma once

#include "script_line.hpp"

class Script
{
public:
	Script() = default;

	void addLine(const string& ID, shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action);
	void removeLine(const string& ID);
	void execute();
	void reset();

	unsigned int getLineCount();

	bool isExisting(const string& ID);

	ScriptLine& getScriptLine(const string& ID);

	vector<string> getAllScriptIDs();

private:
	vector<ScriptLine> _scriptLines;
};