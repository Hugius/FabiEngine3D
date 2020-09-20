#include "script.hpp"
#include "logger.hpp"

void Script::addLine(const string& ID, shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action)
{
	ScriptLine scriptLine;
	scriptLine.ID = ID;
	scriptLine.event = event;
	scriptLine.action = action;

	_scriptLines.push_back(scriptLine);
}

void Script::removeLine(const string& ID)
{
	int index = 0;

	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.ID == ID)
		{
			_scriptLines.erase(_scriptLines.begin() + index);
			return;
		}
		index++;
	}

	Logger::getInst().throwError("Could not erase script line with ID: " + ID);
}

void Script::execute()
{
	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.event != nullptr && scriptLine.action != nullptr)
		{
			if (scriptLine.event->isTriggered())
			{
				scriptLine.action->execute();
			}
		}
	}
}

void Script::reset()
{
	// Reset all initialization events
	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.event->getType() == ScriptEventType::INITIALIZATION)
		{
			scriptLine.event->reset();
		}
	}

	// Reset all actions
	for (auto& scriptLine : _scriptLines)
	{
		scriptLine.action->reset();
	}
}

unsigned int Script::getLineCount()
{
	return _scriptLines.size();
}

bool Script::isExisting(const string& ID)
{
	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.ID == ID)
		{
			return true;
		}
	}

	return false;
}

ScriptLine& Script::getScriptLine(const string& ID)
{
	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.ID == ID)
		{
			return scriptLine;
		}
	}

	Logger::getInst().throwError("Could not find script line with ID: " + ID);
}

vector<string> Script::getAllScriptLineIDs()
{
	vector<string> result;

	for (auto& scriptLine : _scriptLines)
	{
		result.push_back(scriptLine.ID);
	}

	return result;
}
