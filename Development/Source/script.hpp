#pragma once

#include "script_line.hpp"
#include "script_variable.hpp"

class Script
{
public:
	Script() = default;

	void addVariable(const string& ID, shared_ptr<ScriptValue> value);
	void removeVariable(const string& ID);
	void addLine(const string& ID, shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action);
	void removeLine(const string& ID);
	void execute();
	void reset();

	unsigned int getLineCount();
	unsigned int getVariableCount();

	bool isExisting(const string& ID);

	ScriptLine& getScriptLine(const string& ID);
	ScriptVariable& getScriptVariable(const string& ID);

	vector<string> getAllScriptLineIDs();
	vector<string> getAllScriptVariableIDs();

private:
	vector<ScriptVariable> _scriptVariables;
	vector<ScriptLine> _scriptLines;
};