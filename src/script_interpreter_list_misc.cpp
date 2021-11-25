#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(const ScriptVariable& list, unsigned int index)
{
	// Check if variable is not a list
	if(list.getType() == ScriptVariableType::SINGLE)
	{
		_throwScriptError("variable is not a LIST!");
		return false;
	}

	// Check if list index is negative
	if(index < 0)
	{
		_throwScriptError("LIST index is negative!");
		return false;
	}

	// Check if list index is out of range
	if(index >= list.getValueCount())
	{
		_throwScriptError("LIST index is out of range!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateArgumentCount(const vector<ScriptValue>& values, unsigned int count)
{
	if(values.size() == count) // Correct amount of arguments
	{
		return true;
	}
	else if(values.size() < count) // Not enough arguments
	{
		_throwScriptError("not enough arguments!");
		return false;
	}
	else // Too many arguments
	{
		_throwScriptError("too many arguments!");
		return false;
	}
}

const bool ScriptInterpreter::_validateArgumentTypes(const vector<ScriptValue>& values, const vector<ScriptValueType>& types)
{
	// Iterate through values
	for(size_t i = 0; i < values.size(); i++)
	{
		// Compare value types
		if(values[i].getType() != types[i])
		{
			_throwScriptError("incorrect argument type" + string((values.size() == 1) ? "" : "s") + "!");
			return false;
		}
	}

	return true;
}

void ScriptInterpreter::_processListPush(const string& scriptLine)
{
	// Extract list name
	string nameString = "";
	for(const auto& c : scriptLine.substr(PUSHING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	// Check if list name is missing
	if(nameString.empty())
	{
		_throwScriptError("LIST name missing!");
		return;
	}

	// Check if value is present
	if(scriptLine.size() < (PUSHING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwScriptError("LIST value missing!");
		return;
	}

	// Extract value
	string valueString = scriptLine.substr(PUSHING_KEYWORD.size() + nameString.size() + 2);

	// Check if list exists
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if list is constant
	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to constant LIST!");
		return;
	}

	// Determine value type
	if(_isListValue(valueString)) // LIST
	{
		_throwScriptError("cannot push LIST to LIST!");
		return;
	}
	else if(_isStringValue(valueString)) // STR
	{
		// Remove the []
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Add value
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::STRING, valueString));
	}
	else if(_isDecimalValue(valueString)) // DEC
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))));
	}
	else if(_isIntegerValue(valueString)) // INT
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))));
	}
	else if(_isBooleanValue(valueString)) // BOOL
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>")));
	}
	else
	{
		// Check if variable is not existing
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("invalid value!");
			return;
		}

		// Retrieve right variable
		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Check if pushing list to list
		if(rightVariable.getType() == ScriptVariableType::MULTIPLE)
		{
			_throwScriptError("cannot push LIST to LIST!");
			return;
		}

		// Add value
		listVariable.addValue(rightVariable.getValue());
	}
}

void ScriptInterpreter::_processListPull(const string& scriptLine)
{
	// Extract list name
	 string nameString = "";
	for(const auto& c : scriptLine.substr(PULLING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	// Check if list name is missing
	if(nameString.empty())
	{
		_throwScriptError("LIST name missing!");
		return;
	}

	// Check if list index is missing
	if(scriptLine.size() < (PULLING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwScriptError("LIST index missing!");
		return;
	}

	// Extract list index
	string indexString = scriptLine.substr(PULLING_KEYWORD.size() + nameString.size() + 2);

	// Check if list index is invalid
	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwScriptError("invalid LIST index!");
		return;
	}

	// Check if list is not existing
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if list is constant
	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to constant LIST!");
		return;
	}

	// Convert list index
	unsigned int index = -1;
	if(_isIntegerValue(indexString)) // Integer index
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else // Variable index
	{
		// Retrieve index variable
		auto indexVariable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		// Check if not integer
		if(indexVariable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("LIST index not of type INT!");
			return;
		}

		// Set index
		index = indexVariable.getValue().getInteger();
	}

	// Validate list index
	if(!_validateListIndex(listVariable, index))
	{
		return;
	}

	// Remove value
	listVariable.removeValue(index);
}