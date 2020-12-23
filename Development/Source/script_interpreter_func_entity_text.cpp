#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dTextEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("Requested text ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.textEntity_isExisting(ID))
	{
		_throwScriptError("Requested text with ID \"" + ID + "\" does not exist!");

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dTextEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	return false;
}