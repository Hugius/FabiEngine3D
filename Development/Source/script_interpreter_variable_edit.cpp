#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableAlteration(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string typeString = "";
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;

	// Extract text parts
	string keyword;
	iss >> keyword >> nameString >> equalSignString;

	// Extract remaining text (value)
	if (equalSignString == "=")
	{
		valueString = scriptLine.substr(scriptLine.find('=') + 2);
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

	// Check if equal sign is valid
	if (equalSignString == "=")
	{
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
		else if (variable.getType() == ScriptVariableType::SINGLE &&
			variable.getValue().getType() == ScriptValueType::VEC3 && _isVec3Value(valueString)) // VEC3
		{
			variable.getValue().setVec3(_extractVec3FromString(valueString));
		}
		else if (variable.getType() == ScriptVariableType::SINGLE &&
			variable.getValue().getType() == ScriptValueType::STRING && _isStringValue(valueString)) // STRING
		{
			valueString.erase(valueString.begin());
			valueString.pop_back();
			variable.getValue().setString(valueString);
		}
		else if (variable.getType() == ScriptVariableType::SINGLE &&
			variable.getValue().getType() == ScriptValueType::DECIMAL && _isDecimalValue(valueString)) // DECIMAL
		{
			variable.getValue().setDecimal(stof(valueString));
		}
		else if (variable.getType() == ScriptVariableType::SINGLE &&
			variable.getValue().getType() == ScriptValueType::INTEGER && _isIntegerValue(valueString)) // INTEGER
		{
			variable.getValue().setInteger(stoi(valueString));
		}
		else if (variable.getType() == ScriptVariableType::SINGLE &&
			variable.getValue().getType() == ScriptValueType::BOOLEAN && _isBooleanValue(valueString)) // BOOLEAN - normal
		{
			variable.getValue().setBoolean(valueString == "<true>");
		}
		else if // BOOLEAN - condition
			(
				variable.getType() == ScriptVariableType::SINGLE &&
				(variable.getValue().getType() == ScriptValueType::BOOLEAN) &&
				(valueString.front() == '(' && valueString.back() == ')')
				)
		{
			valueString.erase(valueString.begin());
			valueString.pop_back();
			variable.getValue().setBoolean(_checkConditionString(valueString));
		}
		else if // FUNCTION
			(
				valueString.substr(0, 5) == "fe3d:" ||
				valueString.substr(0, 5) == "math:" ||
				valueString.substr(0, 5) == "misc:"
				)
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
			if ((variable.getValue().getType() == ScriptValueType::VEC3) && (values[0].getType() == ScriptValueType::VEC3))
			{
				variable.getValue().setVec3(values[0].getVec3());
			}
			else if ((variable.getValue().getType() == ScriptValueType::STRING) && (values[0].getType() == ScriptValueType::STRING))
			{
				variable.getValue().setString(values[0].getString());
			}
			else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (values[0].getType() == ScriptValueType::DECIMAL))
			{
				variable.getValue().setDecimal(values[0].getDecimal());
			}
			else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (values[0].getType() == ScriptValueType::INTEGER))
			{
				variable.getValue().setInteger(values[0].getInteger());
			}
			else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (values[0].getType() == ScriptValueType::BOOLEAN))
			{
				variable.getValue().setBoolean(values[0].getBoolean());
			}
			else if (values[0].getType() == ScriptValueType::EMPTY)
			{
				_throwScriptError("function must return a value!");
			}
			else
			{
				_throwScriptError("function value type does not match the variable type!");
			}
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

				// Prepare list access
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

				// Check if using part of list variable as value
				if (variable.getValue().getType() == ScriptValueType::DECIMAL && vec3Parts != Ivec3(0))
				{
					if (vec3Parts.x && otherVariable.getValue().getType() == ScriptValueType::VEC3)
					{
						variable.getValue().setDecimal(otherVariable.getValue().getVec3().x);
					}
					else if (vec3Parts.y && otherVariable.getValue().getType() == ScriptValueType::VEC3)
					{
						variable.getValue().setDecimal(otherVariable.getValue().getVec3().y);
					}
					else if (vec3Parts.z && otherVariable.getValue().getType() == ScriptValueType::VEC3)
					{
						variable.getValue().setDecimal(otherVariable.getValue().getVec3().z);
					}
				}
				else if ((otherVariable.getType() == ScriptVariableType::SINGLE || isAccessingList) && // Check if the value types match
					variable.getValue().getType() == otherVariable.getValue().getType())
				{
					variable.changeValue(otherVariable.getValue(), valueIndex);
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
	else
	{
		_throwScriptError("invalid syntax!");
	}
}