#include "script.hpp"
#include "logger.hpp"

void Script::addVariable(const string& ID, shared_ptr<ScriptValue> value)
{
	// Check if non-existent
	for (auto& variable : _scriptVariables)
	{
		if (variable.ID == ID)
		{
			Logger::getInst().throwError("Cannot add script variable, already exists: " + variable.ID);
		}
	}

	// Add new script variable
	ScriptVariable variable;
	variable.ID = ID;
	variable.value = value;
	_scriptVariables.push_back(variable);
}

void Script::removeVariable(const string& ID)
{
	int index = 0;

	for (auto& variable : _scriptVariables)
	{
		if (variable.ID == ID)
		{
			_scriptVariables.erase(_scriptVariables.begin() + index);
			return;
		}
		index++;
	}

	Logger::getInst().throwError("Cannot erase script variable with ID: " + ID);
}

void Script::addLine(const string& ID, shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action)
{
	// Check if non-existent
	for (auto& line : _scriptLines)
	{
		if (line.ID == ID)
		{
			Logger::getInst().throwError("Cannot add script line, already exists: " + ID);
		}
	}

	// Add new script line
	ScriptLine scriptLine;
	scriptLine.ID = ID;
	scriptLine.event = event;
	scriptLine.action = action;
	_scriptLines.push_back(scriptLine);
}

void Script::removeLine(const string& ID)
{
	int index = 0;

	for (auto& line : _scriptLines)
	{
		if (line.ID == ID)
		{
			_scriptLines.erase(_scriptLines.begin() + index);
			return;
		}
		index++;
	}

	Logger::getInst().throwError("Cannot erase script line with ID: " + ID);
}

void Script::execute()
{
	for (auto& line : _scriptLines)
	{
		if (line.event != nullptr && line.action != nullptr)
		{
			if (line.event->isTriggered())
			{
				line.action->execute();
			}
		}
	}
}

void Script::reset()
{
	// Reset all initialization events
	for (auto& line : _scriptLines)
	{
		if (line.event->getType() == ScriptEventType::INITIALIZATION)
		{
			line.event->reset();
		}
	}

	// Reset all actions
	for (auto& line : _scriptLines)
	{
		line.action->reset();
	}
}

unsigned int Script::getLineCount()
{
	return _scriptLines.size();
}

unsigned int Script::getVariableCount()
{
	return _scriptVariables.size();
}

bool Script::isExisting(const string& ID)
{
	for (auto& line : _scriptLines)
	{
		if (line.ID == ID)
		{
			return true;
		}
	}

	return false;
}

ScriptLine& Script::getScriptLine(const string& ID)
{
	for (auto& line : _scriptLines)
	{
		if (line.ID == ID)
		{
			return line;
		}
	}

	Logger::getInst().throwError("Could not find script line with ID: " + ID);
}

ScriptVariable& Script::getScriptVariable(const string& ID)
{
	for (auto& variable : _scriptVariables)
	{
		if (variable.ID == ID)
		{
			return variable;
		}
	}

	Logger::getInst().throwError("Could not find script variable with ID: " + ID);
}

vector<string> Script::getAllScriptLineIDs()
{
	vector<string> result;

	for (auto& line : _scriptLines)
	{
		result.push_back(line.ID);
	}

	return result;
}

vector<string> Script::getAllScriptVariableIDs()
{
	vector<string> result;

	for (auto& variable : _scriptVariables)
	{
		result.push_back(variable.ID);
	}

	return result;
}
