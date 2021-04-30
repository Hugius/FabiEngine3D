#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableAlteration(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string equalSignString = "";
	string valueString = "";
	bool isConstant = false;
	unsigned int valueIndexOne = 0;

	// Extract name & equal sign
	string words[2] = { "", "" };
	unsigned int wordIndex = 0;
	for (const auto& c : scriptLine.substr(EDIT_KEYWORD.size() + 1))
	{
		if (c == ' ') // Current word ended
		{
			// Next word
			wordIndex++;

			// Check if words extracted
			if (wordIndex == 2)
			{
				break;
			}
		}
		else // Add to word
		{
			words[wordIndex] += c;
		}
	}
	nameString = words[0];
	equalSignString = words[1];

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
	bool isAccessingListOne = false;
	auto listIndexOne = _extractListIndexFromString(nameString, isAccessingListOne);

	// Check if changing individual float from vec3 variable
	auto vec3PartsOne = _extractVec3PartFromString(nameString);

	// Check if any error was thrown
	if (_hasThrownError)
	{
		return;
	}

	// Remove vec3 part characters
	if (vec3PartsOne != Ivec3(0))
	{
		nameString.pop_back();
		nameString.pop_back();
	}

	// Remove list accessing characters
	if (isAccessingListOne)
	{
		auto openingBracketFound = std::find(nameString.begin(), nameString.end(), '[');
		auto bracketIndex = static_cast<unsigned int>(std::distance(nameString.begin(), openingBracketFound));
		nameString = nameString.substr(0, bracketIndex);
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable not existing!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// A constant variable should not be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable cannot be changed: it is constant!");
		return;
	}

	// Validate vec3 access
	if (vec3PartsOne != Ivec3(0))
	{
		if (variable.getType() == ScriptVariableType::MULTIPLE || variable.getValue().getType() != ScriptValueType::VEC3)
		{
			_throwScriptError("variable is not a vec3!");
			return;
		}
	}

	// Validate list access
	if (isAccessingListOne)
	{
		// Check if list index is valid
		if (_validateListIndex(variable, listIndexOne))
		{
			valueIndexOne = listIndexOne;
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
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::VEC3 && _isVec3Value(valueString) && vec3PartsOne == Ivec3(0)) // VEC3
	{
		variable.getValue(valueIndexOne).setVec3(_extractVec3FromString(valueString));
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::STRING && _isStringValue(valueString)) // STRING
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variable.getValue(valueIndexOne).setString(valueString);
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL && _isDecimalValue(valueString)) // DECIMAL - normal
	{
		variable.getValue(valueIndexOne).setDecimal(stof(_limitDecimalString(valueString)));
	}
	else if (variable.getType() == ScriptVariableType::SINGLE && vec3PartsOne != Ivec3(0) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::VEC3 && _isDecimalValue(valueString)) // DECIMAL - vec3 part
	{
		auto oldValue = variable.getValue(valueIndexOne).getVec3();

		// Determine which part of vec3 must change
		if (vec3PartsOne.x)
		{
			variable.getValue(valueIndexOne).setVec3(Vec3(stof(_limitDecimalString(valueString)), oldValue.y, oldValue.z));
		}
		else if (vec3PartsOne.y)
		{
			variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, stof(_limitDecimalString(valueString)), oldValue.z));
		}
		else if (vec3PartsOne.z)
		{
			variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, stof(_limitDecimalString(valueString))));
		}
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER && _isIntegerValue(valueString)) // INTEGER
	{
		variable.getValue(valueIndexOne).setInteger(stoi(_limitIntegerString(valueString)));
	}
	else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
		variable.getValue(valueIndexOne).getType() == ScriptValueType::BOOLEAN && _isBooleanValue(valueString)) // BOOLEAN - normal
	{
		variable.getValue(valueIndexOne).setBoolean(valueString == "<true>");
	}
	else if // BOOLEAN - condition
		(
			(variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) &&
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::BOOLEAN) &&
			(valueString.front() == '(' && valueString.back() == ')')
		)
	{
		valueString.erase(valueString.begin());
		valueString.pop_back();
		variable.getValue(valueIndexOne).setBoolean(_checkConditionString(valueString));
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

		if (variable.getType() == ScriptVariableType::MULTIPLE) // Check if variable is an list
		{
			variable.changeValues(values);
		}
		else if (values[0].getType() == ScriptValueType::EMPTY) // Check if function returned anything
		{
			_throwScriptError("function must return a value!");
		}
		else if (values.size() > 1) // Check if function returned too many values
		{
			_throwScriptError("function returned too many values!");
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) && 
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::VEC3) &&  // VEC3
			(values[0].getType() == ScriptValueType::VEC3))
		{
			variable.getValue(valueIndexOne).setVec3(values[0].getVec3());
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) && 
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::STRING) &&  // STRING
			(values[0].getType() == ScriptValueType::STRING))
		{
			variable.getValue(valueIndexOne).setString(values[0].getString());
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) && 
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL) && // DECIMAL - normal
			(values[0].getType() == ScriptValueType::DECIMAL))
		{
			variable.getValue(valueIndexOne).setDecimal(values[0].getDecimal());
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE) && 
			vec3PartsOne != Ivec3(0) && (variable.getValue(valueIndexOne).getType() == ScriptValueType::VEC3) && // DECIMAL - vec3 part
			(values[0].getType() == ScriptValueType::DECIMAL))
		{
			auto oldValue = variable.getValue(valueIndexOne).getVec3();

			// Determine which part of vec3 must change
			if (vec3PartsOne.x)
			{
				variable.getValue(valueIndexOne).setVec3(Vec3(values[0].getDecimal(), oldValue.y, oldValue.z));
			}
			else if (vec3PartsOne.y)
			{
				variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, values[0].getDecimal(), oldValue.z));
			}
			else if (vec3PartsOne.z)
			{
				variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, values[0].getDecimal()));
			}
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) && 
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::INTEGER) && // INTEGER
			(values[0].getType() == ScriptValueType::INTEGER))
		{
			variable.getValue(valueIndexOne).setInteger(values[0].getInteger());
		}
		else if ((variable.getType() == ScriptVariableType::SINGLE || isAccessingListOne) && 
			(variable.getValue(valueIndexOne).getType() == ScriptValueType::BOOLEAN) && // BOOLEAN
			(values[0].getType() == ScriptValueType::BOOLEAN))
		{
			variable.getValue(valueIndexOne).setBoolean(values[0].getBoolean());
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
		bool isAccessingListTwo = false;
		auto listIndexTwo = _extractListIndexFromString(valueString, isAccessingListTwo);

		// Check if accessing individual float from vec3 variable
		auto vec3PartsTwo = _extractVec3PartFromString(valueString);

		// Check if any error was thrown
		if (_hasThrownError)
		{
			return;
		}

		// Remove vec3 part text
		if (vec3PartsTwo != Ivec3(0))
		{
			valueString.pop_back();
			valueString.pop_back();
		}

		// Remove list accessing characters
		if (isAccessingListTwo)
		{
			auto openingBracketFound = std::find(valueString.begin(), valueString.end(), '[');
			auto bracketIndex = static_cast<unsigned int>(std::distance(valueString.begin(), openingBracketFound));
			valueString = valueString.substr(0, bracketIndex);
		}

		// Check if using another variable as value
		if (_isLocalVariableExisting(valueString) || _isGlobalVariableExisting(valueString))
		{
			// Retrieve other value
			auto otherVariable = _isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) :
				_getGlobalVariable(valueString);

			// Validate vec3 access
			if (vec3PartsTwo != Ivec3(0))
			{
				if (otherVariable.getType() == ScriptVariableType::MULTIPLE || otherVariable.getValue().getType() != ScriptValueType::VEC3)
				{
					_throwScriptError("variable is not a vec3!");
					return;
				}
			}

			// Validate list access
			if (isAccessingListTwo)
			{
				// Check if list index is valid
				if (_validateListIndex(otherVariable, listIndexTwo))
				{
					valueIndexTwo = listIndexTwo;
				}
				else // Error
				{
					return;
				}
			}

			// Determine type of variable value
			if (variable.getValue(valueIndexOne).getType() == ScriptValueType::DECIMAL && vec3PartsTwo != Ivec3(0)) // decimal = vec.{xyz}
			{
				// Determine vec3 part
				if (vec3PartsTwo.x)
				{
					variable.getValue(valueIndexOne).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().x);
				}
				else if (vec3PartsTwo.y)
				{
					variable.getValue(valueIndexOne).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().y);
				}
				else if (vec3PartsTwo.z)
				{
					variable.getValue(valueIndexOne).setDecimal(otherVariable.getValue(valueIndexTwo).getVec3().z);
				}
			}
			else if (vec3PartsOne != Ivec3(0) && vec3PartsTwo != Ivec3(0)) // vec.{xyz} = vec.{xyz}
			{
				auto oldValue = variable.getValue(valueIndexOne).getVec3();
				auto newDecimal = vec3PartsTwo.x ? otherVariable.getValue(valueIndexTwo).getVec3().x : vec3PartsTwo.y ?
					otherVariable.getValue(valueIndexTwo).getVec3().y : otherVariable.getValue(valueIndexTwo).getVec3().z;

				// Determine vec3 part
				if (vec3PartsOne.x)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(newDecimal, oldValue.y, oldValue.z));
				}
				else if (vec3PartsOne.y)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, newDecimal, oldValue.z));
				}
				else if (vec3PartsOne.z)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, newDecimal));
				}
			}
			else if (vec3PartsOne != Ivec3(0) && vec3PartsTwo == Ivec3(0)) // vec.{xyz} = decimal
			{
				// Check if other value is not a decimal
				if (otherVariable.getValue(valueIndexTwo).getType() != ScriptValueType::DECIMAL)
				{
					_throwScriptError("variable types do not match!");
					return;
				}

				auto oldValue = variable.getValue(valueIndexOne).getVec3();

				// Determine vec3 part
				if (vec3PartsOne.x)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(otherVariable.getValue(valueIndexTwo).getDecimal(), oldValue.y, oldValue.z));
				}
				else if (vec3PartsOne.y)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, otherVariable.getValue(valueIndexTwo).getDecimal(), oldValue.z));
				}
				else if (vec3PartsOne.z)
				{
					variable.getValue(valueIndexOne).setVec3(Vec3(oldValue.x, oldValue.y, otherVariable.getValue(valueIndexTwo).getDecimal()));
				}
			}
			else if ((otherVariable.getType() == ScriptVariableType::SINGLE || isAccessingListTwo) && // Check if the value types match
				variable.getValue(valueIndexOne).getType() == otherVariable.getValue(valueIndexTwo).getType())
			{
				variable.changeValue(otherVariable.getValue(valueIndexTwo), valueIndexOne);
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