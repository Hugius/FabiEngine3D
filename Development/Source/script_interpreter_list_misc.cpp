#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateListIndex(ScriptVariable& list, unsigned int index)
{
	// Check if variable is a list in the first place
	if (list.getType() == ScriptVariableType::SINGLE)
	{
		_throwScriptError("variable is not a list!");
		return false;
	}

	// Check if list index is valid
	if (index < 0 || index >= list.getValueCount())
	{
		_throwScriptError("list index out of range");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateListValueAmount(vector<ScriptValue> list, unsigned int amount)
{
	if (list.size() == amount) // Check if value amount is correct
	{
		return true;
	}
	else if (list.size() < amount) // Not enough values
	{
		_throwScriptError("not enough values!");
	}
	else // Too many values
	{
		_throwScriptError("too many values!");
	}

	return false;
}

bool ScriptInterpreter::_validateListValueTypes(vector<ScriptValue> list, vector<ScriptValueType> types)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		if (list[i].getType() != types[i])
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
	std::istringstream iss(scriptLine);
	string keyword = "";
	string nameString = "";
	string valueString = "";
	string elementBuild = "";
	unsigned int elementsFound = 0;

	// Extract text parts
	iss >> keyword >> nameString;

	// Check if list name is missing
	if (nameString.empty())
	{
		_throwScriptError("list name missing!");
		return;
	}

	// Extract remaining text (value)
	for (auto& c : scriptLine)
	{
		if (c == ' ' && elementBuild.empty() && valueString.empty()) // Useless whitespace
		{
			continue;
		}
		else if (elementsFound < 2) // Keyword & name
		{
			if (c == ' ') // Whitespace
			{
				elementsFound++;
				elementBuild.clear();
			}
			else
			{
				elementBuild += c;
			}
		}
		else // Value
		{
			valueString += c;
		}
	}

	// Check if list exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("list not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// A constant list should not be changed
	if (listVariable.isConstant())
	{
		_throwScriptError("cannot push to list: it is constant!");
		return;
	}
	
	// Determine value type
	if (_isListValue(valueString)) // LIST
	{
		_throwScriptError("cannot push a list to another list!");
		return;
	}
	else if (_isVec3Value(valueString)) // VEC3
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(valueString)));
	}
	else if (_isStringValue(valueString)) // STRING
	{
		// Removing the "" around the string content
		valueString.erase(valueString.begin());
		valueString.pop_back();

		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::STRING, valueString));
	}
	else if (_isDecimalValue(valueString)) // DECIMAL
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))));
	}
	else if (_isIntegerValue(valueString)) // INTEGER
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))));
	}
	else if (_isBooleanValue(valueString)) // BOOLEAN
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

		// Check if accessing individual float from vec3 variable
		auto vec3Parts = _extractVec3PartFromString(valueString);

		// Check if any error was thrown
		if (_hasThrownError)
		{
			return;
		}

		// Remove vec3 part text
		if (vec3Parts != Ivec3(0))
		{
			valueString.pop_back();
			valueString.pop_back();
		}

		// Remove list accessing characters
		if (isAccessingList)
		{
			auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
			unsigned int bracketIndex = std::distance(valueString.begin(), openingBracketFound);
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if using another variable as value
		if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
		{
			// Retrieve other value
			auto otherVariable = _isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) :
				_getGlobalVariable(valueString);

			// Validate vec3 access
			if (vec3Parts != Ivec3(0))
			{
				if (otherVariable.getType() == ScriptVariableType::MULTIPLE || otherVariable.getValue().getType() != ScriptValueType::VEC3)
				{
					_throwScriptError("variable is not a vec3!");
					return;
				}
			}

			// Validate list access
			if (isAccessingList)
			{
				// Check if list index is valid
				if (_validateListIndex(otherVariable, listIndex))
				{
					valueIndex = listIndex;
				}
				else // Error
				{
					return;
				}
			}

			
			if (otherVariable.getType() == ScriptVariableType::MULTIPLE && !isAccessingList) // List value
			{
				_throwScriptError("cannot push a list to another list!");
				return;
			}
			else if (vec3Parts != Ivec3(0)) // Vec3 part value
			{
				if (vec3Parts.x && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().x));
				}
				else if (vec3Parts.y && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().y));
				}
				else if (vec3Parts.z && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().z));
				}
			}
			else // Normal value (or list access)
			{
				listVariable.addValue(otherVariable.getValue(valueIndex));
			}
		}
		else
		{
			_throwScriptError("invalid value!");
		}
	}
}

void ScriptInterpreter::_processListPull(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string keyword = "";
	string nameString = "";
	string indexString = "";

	// Extract text parts
	iss >> keyword >> nameString >> indexString;

	// Check if variable name is missing
	if (nameString.empty())
	{
		_throwScriptError("list name missing!");
		return;
	}

	// Check if list index is missing
	if (indexString.empty())
	{
		_throwScriptError("list index missing!");
		return;
	}

	// Check if list index is invalid
	if (!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwScriptError("invalid list index!");
		return;
	}

	// Check if list exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("list not existing!");
		return;
	}

	// Retrieve list variable
	auto& listVariable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// A constant list should not be changed
	if (listVariable.isConstant())
	{
		_throwScriptError("cannot push to list: it is constant!");
		return;
	}

	// Determine index
	unsigned int index = -1;
	if (_isIntegerValue(indexString)) // Integer value
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else
	{
		// Retrieve index variable
		auto indexVariable = _isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString);

		// Check if integer
		if (indexVariable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("index variable is not an integer!");
			return;
		}

		// Set index
		index = indexVariable.getValue().getInteger();
	}

	// Check if list index is out of range
	if (!_validateListIndex(listVariable, index))
	{
		return;
	}

	// Pull item from list by index
	listVariable.removeValue(index);
	
	// No characters allowed after variable arithmetic
	string temp;
	if (iss >> temp || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
	}
}