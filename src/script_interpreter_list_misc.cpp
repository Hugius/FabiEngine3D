#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(const ScriptVariable& list, unsigned int index)
{
	// Check if variable is a list in the first place
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

const bool ScriptInterpreter::_validateListValueCount(const vector<ScriptValue>& values, unsigned int count)
{
	if(values.size() == count) // Check if value amount is correct
	{
		return true;
	}
	else if(values.size() < count) // Not enough values
	{
		_throwScriptError("not enough values!");
		return false;
	}
	else // Too many values
	{
		_throwScriptError("too many values!");
		return false;
	}
}

const bool ScriptInterpreter::_validateListValueTypes(const vector<ScriptValue>& values, const vector<ScriptValueType>& types)
{
	for(size_t i = 0; i < values.size(); i++)
	{
		if(values[i].getType() != types[i])
		{
			_throwScriptError("wrong value type(s)!");
			return false;
		}
	}

	return true;
}

void ScriptInterpreter::_processListPush(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string valueString = "";

	// Extract name
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
	if(scriptLine.size() >= (PUSHING_KEYWORD.size() + nameString.size() + 3))
	{
		// Extract remaining text (value)
		valueString = scriptLine.substr(PUSHING_KEYWORD.size() + nameString.size() + 2);
	}
	else
	{
		_throwScriptError("value missing!");
		return;
	}

	// Check if list exists
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// A constant list should not be changed
	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to LIST: it is constant!");
		return;
	}

	// Determine value type
	if(_isListValue(valueString)) // LIST
	{
		_throwScriptError("cannot push a LIST to another list!");
		return;
	}
	else if(_isStringValue(valueString)) // STRING
	{
		// Removing the "" around the string content
		valueString.erase(valueString.begin());
		valueString.pop_back();

		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::STRING, valueString));
	}
	else if(_isDecimalValue(valueString)) // DECIMAL
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))));
	}
	else if(_isIntegerValue(valueString)) // INTEGER
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))));
	}
	else if(_isBooleanValue(valueString)) // BOOLEAN
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, valueString == "<true>"));
	}
	else
	{
		// Temporary values
		unsigned int valueIndex = 0;

		// Check if accessing individual value from list variable
		bool isAccessingList = false;
		auto listIndex = _extractListIndexFromString(valueString, isAccessingList);

		// Check if any error was thrown
		if(_hasThrownError)
		{
			return;
		}

		// Remove list accessing characters
		if(isAccessingList)
		{
			auto openingBracketFound = find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(distance(valueString.begin(), openingBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if using another variable as value
		if(_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
		{
			// Retrieve other value
			auto otherVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

			// Validate list access
			if(isAccessingList)
			{
				// Check if list index is valid
				if(_validateListIndex(otherVariable, listIndex))
				{
					valueIndex = listIndex;
				}
				else // Error
				{
					return;
				}
			}


			if(otherVariable.getType() == ScriptVariableType::MULTIPLE && !isAccessingList) // List value
			{
				_throwScriptError("cannot push a LIST to another list!");
				return;
			}
			else // Normal value (or list access)
			{
				listVariable.addValue(otherVariable.getValue(valueIndex));
			}
		}
		else
		{
			_throwScriptError("invalid value!");
			return;
		}
	}
}

void ScriptInterpreter::_processListPull(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string indexString = "";

	// Extract name
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

	// Check if variable name is missing
	if(nameString.empty())
	{
		_throwScriptError("LIST name missing!");
		return;
	}

	// Check if list index is present
	if(scriptLine.size() >= (PULLING_KEYWORD.size() + nameString.size() + 3))
	{
		// Extract remaining text (value)
		indexString = scriptLine.substr(PULLING_KEYWORD.size() + nameString.size() + 2);
	}
	else
	{
		_throwScriptError("LIST index missing!");
		return;
	}

	// Check if list index is invalid
	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwScriptError("invalid LIST index!");
		return;
	}

	// Check if list exists
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// A constant list should not be changed
	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to LIST: it is constant!");
		return;
	}

	// Determine index
	unsigned int index = -1;
	if(_isIntegerValue(indexString)) // Integer value
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else
	{
		// Retrieve index variable
		auto indexVariable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		// Check if integer
		if(indexVariable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("index variable is not an INT!");
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

	// Pull item from list by index
	listVariable.removeValue(index);
}