#include "script.hpp"

Script::Script()
{

}

void Script::addLine(shared_ptr<ScriptEvent> event, shared_ptr<ScriptAction> action)
{
	_scriptLines.push_back(std::make_pair(event, action));
}

void Script::removeLine(int lineNumber)
{
	_scriptLines.erase(_scriptLines.begin() + lineNumber, _scriptLines.end());
}

void Script::execute()
{
	for (auto& scriptLine : _scriptLines)
	{
		if (scriptLine.first->isTriggered())
		{
			scriptLine.second->execute();
		}
	}
}