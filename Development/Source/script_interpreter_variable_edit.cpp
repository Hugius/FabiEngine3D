#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableAlteration(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string keyword;
	string typeString = "";
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;
	unsigned int valueIndex = 0;

	// Extract text parts
	iss >> keyword >> nameString >> equalSignString;

	// Check if variable name is missing
	if (nameString.empty())
	{
		_throwScriptError("variable name missing!");
		return;
	}

	// Check if equal string is present
	if (equalSignString == "=")
	{
		// Check if value is present
		if (scriptLine.size() - 1 >= scriptLine.find('=') + 2)
		{
			// Extract remaining text (value)
			valueString = scriptLine.substr(scriptLine.find('=') + 2);
			begin :
			for (unsigned int i = 0; i < valueString.size(); i++)
			{
				if (valueString[i] == ' ')
				{
					valueString.erase(valueString.begin() + i);
					goto begin;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			_throwScriptError("invalid value syntax!");
			return;
		}
	}
	else
	{
		_throwScriptError("equal sign missing!");
		return;
	}

	// Check if changing individual value from list variable
	bool isAccessingList = false;
	auto listIndex = _extractListIndexFromString(nameString, isAccessingList);

	// Check if changing individual float from vec3 variable
	auto vec3Parts = _extractVec3PartFromString(nameString);

	// Check if any error was thrown
	if (_hasThrownError)
	{
		return;
	}

	// Remove vec3 part characters
	if (vec3Parts != Ivec3(0))
	{
		nameString.pop_back();
		nameString.pop_back();
	}

	// Remove list accessing characters
	if (isAccessingList)
	{
		auto openingBracketFound = std::find(nameString.begin(), nameString.end(), '[');
		unsigned int bracketIndex = std::distance(nameString.begin(), openingBracketFound);
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// A constant variable should not be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be changed, it is constant!");
		return;
	}

	// Validate vec3 access
	if (vec3Parts != Ivec3(0))
	{
		if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::VEC3)
		{
			_throwScriptError("variable with ID \"" + variable.getID() + "\" is not a vec3!");
			return;
		}
	}

	// Validate list access
	if (isAccessingList)
	{
		// Check if list index is valid
		if (_validateListIndex(variable, listIndex))
		{
			valueIndex = listIndex;
		}
		else // Error
		{
			return;
		}
	}

	// Determine value type
	if (variable.getType() == ScriptVariableType::MULTIPLE && _isListValue(valueString)) // LIST
	{
		// Removing the "" around the string content
		string listString = valueString.substr(1);
		listString.pop_back();

		// Extract the values
		auto values = _extractValuesFromListString(listString);
		variable.changeValues(values);
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::VEC3 && _isVec3Value(valueString) && vec3Parts == Ivec3(0)) // VEC3
	{
		variable.getValue(valueIndex).setVec3(_extractVec3FromString(valueString));
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::STRING && _isStringValue(valueString)) // STRING
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variable.getValue(valueIndex).setString(valueString);
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL && _isDecimalValue(valueString)) // DECIMAL - normal
	{
		variable.getValue(valueIndex).setDecimal(stof(valueString));
	}
	else if (vec3Parts != Ivec3(0) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::VEC3 && _isDecimalValue(valueString)) // DECIMAL - vec3 part
	{
		auto oldValue = variable.getValue(valueIndex).getVec3();

		// Determine which part of vec3 must change
		if (vec3Parts.x)
		{
			variable.getValue(valueIndex).setVec3(Vec3(stof(valueString), oldValue.y, oldValue.z));
		}
		else if (vec3Parts.y)
		{
			variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, stof(valueString), oldValue.z));
		}
		else if (vec3Parts.z)
		{
			variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, oldValue.y, stof(valueString)));
		}
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::INTEGER && _isIntegerValue(valueString)) // INTEGER
	{
		variable.getValue(valueIndex).setInteger(stoi(valueString));
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
		variable.getValue(valueIndex).getType() == ScriptValueType::BOOLEAN && _isBooleanValue(valueString)) // BOOLEAN - normal
	{
		variable.getValue(valueIndex).setBoolean(valueString == "<true>");
	}
	else if // BOOLEAN - condition
		(
			(variable.getType() == ScriptVariableType::SINGLE || isAccessingList) &&
			(variable.getValue(valueIndex).getType() == ScriptValueType::BOOLEAN) &&
			(valueString.front() == '(' && valueString.back() == ')')
		)
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variable.getValue(valueIndex).setBoolean(_checkConditionString(valueString));
	}
	else if (valueString.substr(0, 5) == "fe3d:" || valueString.substr(0, 5) == "math:" || valueString.substr(0, 5) == "misc:") // FUNCTION
	{
		// Call function
		auto values =
			(valueString.substr(0, 5) == "fe3d:") ? _processEngineFunctionCall(valueString) :
			(valueString.substr(0, 5) == "math:") ? _processMathematicalFunctionCall(valueString) :
			_processMiscellaneousFunctionCall(valueString);

		// Check if any error was thrown
		if (_hasThrownError)
		{
			return;
		}

		// Check if returned value is of the right type
		if (values.size() > 1)
		{
			if (variable.getType() == ScriptVariableType::MULTIPLE) // Variable is an array
			{
				variable.changeValues(values);
			}
			else // Variable is not an array
			{
				_throwScriptError("function returned too many values!");
			}
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::VEC3) &&  // VEC3
			(values[0].getType() == ScriptValueType::VEC3))
		{
			variable.getValue(valueIndex).setVec3(values[0].getVec3());
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::STRING) &&  // STRING
			(values[0].getType() == ScriptValueType::STRING))
		{
			variable.getValue(valueIndex).setString(values[0].getString());
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL) && // DECIMAL - normal
			(values[0].getType() == ScriptValueType::DECIMAL))
		{
			variable.getValue(valueIndex).setDecimal(values[0].getDecimal());
		}
		else if (vec3Parts != Ivec3(0) && (variable.getValue(valueIndex).getType() == ScriptValueType::VEC3) && // DECIMAL - vec3 part
			(values[0].getType() == ScriptValueType::DECIMAL))
		{
			auto oldValue = variable.getValue(valueIndex).getVec3();

			// Determine which part of vec3 must change
			if (vec3Parts.x)
			{
				variable.getValue(valueIndex).setVec3(Vec3(values[0].getDecimal(), oldValue.y, oldValue.z));
			}
			else if (vec3Parts.y)
			{
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, values[0].getDecimal(), oldValue.z));
			}
			else if (vec3Parts.z)
			{
				variable.getValue(valueIndex).setVec3(Vec3(oldValue.x, oldValue.y, values[0].getDecimal()));
			}
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::INTEGER) &&  // INTEGER
			(values[0].getType() == ScriptValueType::INTEGER))
		{
			variable.getValue(valueIndex).setInteger(values[0].getInteger());
		}
		else if ((variable.getValue(valueIndex).getType() == ScriptValueType::BOOLEAN) &&  // BOOLEAN
			(values[0].getType() == ScriptValueType::BOOLEAN))
		{
			variable.getValue(valueIndex).setBoolean(values[0].getBoolean());
		}
		else if (values[0].getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("function must return a value!");
		}
		else
		{
			_throwScriptError("function type does not match the variable type!");
		}
	}
	else
	{
		// Temporary values
		unsigned int valueIndexTwo = 0;

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
					valueIndexTwo = listIndex;
				}
				else // Error
				{
					return;
				}
			}

			// Check if using part of vec3 variable as value
			if (variable.getValue(valueIndex).getType() == ScriptValueType::DECIMAL && vec3Parts != Ivec3(0))
			{
				if (vec3Parts.x && otherVariable.getValue(valueIndexTwo).getType() == ScriptValueType::VEC3)
				{
					variable.getValue(valueIndex).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().x);
				}
				else if (vec3Parts.y && otherVariable.getValue(valueIndexTwo).getType() == ScriptValueType::VEC3)
				{
					variable.getValue(valueIndex).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().y);
				}
				else if (vec3Parts.z && otherVariable.getValue(valueIndexTwo).getType() == ScriptValueType::VEC3)
				{
					variable.getValue(valueIndex).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().z);
				}
			}
			else if ((otherVariable.getType() == ScriptVariableType::SINGLE || isAccessingList) && // Check if the value types match
				variable.getValue(valueIndex).getType() == otherVariable.getValue(valueIndexTwo).getType())
			{
				variable.changeValue(otherVariable.getValue(valueIndexTwo), valueIndex);
			}
			else
			{
				_throwScriptError("variable types do not match!");
			}
		}
		else
		{
			_throwScriptError("invalid value!");
		}
	}
}