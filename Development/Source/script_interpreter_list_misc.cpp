#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateListIndex(ScriptVariable& list, unsigned int index)
{
	// Check if variable is a list in the first place
	if (list.getType() == ScriptVariableType::SINGLE)
	{
		_throwScriptError("variable with ID \"" + list.getID() + "\" is not a list!");
		return false;
	}

	// Check if list index is valid
	if (index < 0 || index >= list.getValueCount())
	{
		_throwScriptError("invalid list index!");
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
	unsigned int index = 0;
	bool foundFirstChar = false;

	// Extract text parts
	iss >> keyword >> nameString;

	// Check if variable name is missing
	if (nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Extract remaining text (value)
	for (auto& c : scriptLine)
	{
		if (!foundFirstChar) // Need to find first character
		{
			if (c != ' ') // Ignore whitespace
			{
				foundFirstChar = true;
			}
		}
		else if (elementsFound < 2) // Keyword & name
		{
			if (c == ' ') // Whitespace
			{
				elementsFound++;
			}
		}
		else // Value
		{
			valueString += c;
		}
	}
	
	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("list variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// A constant variable should not be changed
	if (variable.isConstant())
	{
		_throwScriptError("cannot push to list variable \"" + nameString + "\", it is constant!");
		return;
	}
	
	// Determine value type
	if (_isListValue(valueString)) // LIST
	{
		_throwScriptError("cannot push list to a list variable!");
		return;
	}
	else if (_isVec3Value(valueString)) // VEC3
	{
		variable.addValue(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(valueString)));
	}
	else if (_isStringValue(valueString)) // STRING
	{
		variable.addValue(ScriptValue(_fe3d, ScriptValueType::STRING, valueString));
	}
	else if (_isDecimalValue(valueString)) // DECIMAL
	{
		variable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString)));
	}
	else if (_isIntegerValue(valueString)) // INTEGER
	{
		variable.addValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString)));
	}
	else if (_isBooleanValue(valueString)) // BOOLEAN
	{
		variable.addValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, valueString == "<true>"));
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
					_throwScriptError("variable with ID \"" + otherVariable.getID() + "\" is not a vec3!");
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
				_throwScriptError("cannot push list to a list variable!");
				return;
			}
			else if (vec3Parts != Ivec3(0)) // Vec3 part value
			{
				if (vec3Parts.x && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					variable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().x));
				}
				else if (vec3Parts.y && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					variable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().y));
				}
				else if (vec3Parts.z && otherVariable.getValue(valueIndex).getType() == ScriptValueType::VEC3)
				{
					variable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, otherVariable.getValue(valueIndex).getVec3().z));
				}
			}
			else // Normal value (or list access)
			{
				variable.addValue(otherVariable.getValue(valueIndex));
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

}