#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string operatorString = "";
	string nameString = "";
	string valueString = "";

	// Extract data
	iss >> operatorString >> nameString;

	// Only extract value if not negating
	if (operatorString != _negationKeyword)
	{
		iss >> valueString;
	}

	// Check if valid arithmetic keyword
	if (operatorString != _additionKeyword && operatorString != _subtractionKeyword && operatorString != _multiplicationKeyword && 
		operatorString != _divisionKeyword && operatorString != _negationKeyword)
	{
		_throwScriptError("invalid arithmetic operator!");
		return;
	}

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Check if variable is of the correct type
	if (!(variable.getValue().getType() == ScriptValueType::INTEGER) &&
		!(variable.getValue().getType() == ScriptValueType::DECIMAL) &&
		!(variable.getValue().getType() == ScriptValueType::VEC3))
	{
		_throwScriptError("arithmetic is only allowed on number values!");
		return;
	}

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be changed, it is constant!");
		return;
	}

	// Negation arithmetic operation
	if (operatorString == _negationKeyword)
	{
		if (variable.getValue().getType() == ScriptValueType::INTEGER)
		{
			variable.getValue().setInteger(variable.getValue().getInteger() * -1);
		}
		else if (variable.getValue().getType() == ScriptValueType::DECIMAL)
		{
			variable.getValue().setDecimal(variable.getValue().getDecimal() * -1.0f);
		}
		else if (variable.getValue().getType() == ScriptValueType::VEC3)
		{
			variable.getValue().setVec3(variable.getValue().getVec3() * -1.0f);
		}
	}
	else // Other arithmetic operations
	{
		// Check if value is not empty
		if (valueString.empty())
		{
			_throwScriptError("no arithmetic value found!");
			return;
		}

		// Retrieve arithmetic value
		auto value = _isLocalVariableExisting(valueString) ? _getLocalVariable(valueString).getValue() : _isGlobalVariableExisting(valueString) ?
			_getGlobalVariable(nameString).getValue() : _isIntegerValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString)) :
			_isDecimalValue(valueString) ? ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString)) : ScriptValue(_fe3d, ScriptValueType::EMPTY);

		// Check if arithmetic value is valid
		if (value.getType() == ScriptValueType::EMPTY)
		{
			_throwScriptError("invalid arithmetic value!");
			return;
		}

		// Execute arithmetic operation
		if ((variable.getValue().getType() == ScriptValueType::INTEGER) && value.getType() == ScriptValueType::INTEGER) // Integer
		{
			// Retrieve current variable value
			int result = variable.getValue().getInteger();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getInteger();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getInteger();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getInteger();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getInteger();
			}

			// Set resulting value
			variable.getValue().setInteger(result);
		}
		else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && value.getType() == ScriptValueType::DECIMAL) // Decimal
		{
			// Retrieve current variable value
			float result = variable.getValue().getDecimal();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getDecimal();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			variable.getValue().setDecimal(result);
		}
		else if ((variable.getValue().getType() == ScriptValueType::VEC3) && value.getType() == ScriptValueType::DECIMAL) // Vec3
		{
			// Retrieve current variable value
			Vec3 result = variable.getValue().getVec3();

			// Determine arithmetic type
			if (operatorString == _additionKeyword)
			{
				result += value.getDecimal();
			}
			else if (operatorString == _subtractionKeyword)
			{
				result -= value.getDecimal();
			}
			else if (operatorString == _multiplicationKeyword)
			{
				result *= value.getDecimal();
			}
			else if (operatorString == _divisionKeyword)
			{
				result /= value.getDecimal();
			}

			// Set resulting value
			variable.getValue().setVec3(result);
		}
		else
		{
			_throwScriptError("arithmetic value not applicable to this variable!");
			return;
		}
	}

	// No characters allowed after variable arithmetic
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
	}
}

void ScriptInterpreter::_processVariableTypecast(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string keyword = "";
	string nameString = "";
	string typeString = "";

	// Extract data
	iss >> keyword >> nameString >> typeString;

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be typecasted, it is constant!");
		return;
	}

	// Check if type is not empty
	if (typeString.empty())
	{
		_throwScriptError("no new type found!");
		return;
	}

	// Determine to which new type the variable must cast
	if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == _decimalKeyword)) // From integer to decimal
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, static_cast<float>(variable.getValue().getInteger())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == _integerKeyword)) // From decimal to integer
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getDecimal())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == _integerKeyword)) // From boolean to integer
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getBoolean())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == _stringKeyword)) // From integer to string
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getInteger())));
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == _stringKeyword)) // From decimal to string
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getDecimal())));
	}
	else
	{
		_throwScriptError("variable \"" + nameString + "\" cannot be typecasted, wrong type!");
		return;
	}

	// No characters allowed after variable arithmetic
	string temp;
	if ((iss >> temp) || scriptLine.back() == ' ')
	{
		_throwScriptError("invalid syntax!");
		return;
	}
}

void ScriptInterpreter::_processStringConcatenation(const string& scriptLine)
{
	// Temporary values
	vector<string> elements;
	string elementBuild = "";
	unsigned int index = 0;
	bool buildingString = false;

	// Extract all invidual elements of the scriptline
	for (auto& c : scriptLine)
	{
		if(elements.size() == 3) // No characters allowed after string value
		{
			_throwScriptError("invalid syntax!");
			return;
		}
		else if (index == scriptLine.size() - 1) // Check if last character
		{
			elementBuild += c;
			elements.push_back(elementBuild);
		}
		else if ((c == ' ' && !buildingString)) // Check for whitespace
		{
			elements.push_back(elementBuild);
			elementBuild = "";
		}
		else // Keep building string
		{
			if (c == '"' && !buildingString)
			{
				buildingString = true;
			}
			else if (c == '"' && buildingString)
			{
				buildingString = false;
			}

			// Add character
			elementBuild += c;
		}

		index++;
	}

	// Concatenation statement elements
	string keyword = elements[0];
	string nameString = elements[1];
	string valueString = elements[2];

	// Check if variable exists
	if (!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not found!");
		return;
	}

	// Retrieve variable
	auto& variable = _isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString);

	// Check if variable can be changed
	if (variable.isConstant())
	{
		_throwScriptError("string variable \"" + nameString + "\" cannot be concatenated, it is constant!");
		return;
	}

	// Check if variable value is of type string
	if (variable.getValue().getType() != ScriptValueType::STRING)
	{
		_throwScriptError("concatenation only allowed on string variables!");
		return;
	}

	// Check if value is not empty
	if (valueString.empty())
	{
		_throwScriptError("no value found!");
		return;
	}
	
	// Check if concatenation value is a string
	if (!_isStringValue(valueString))
	{
		_throwScriptError("can only concatenate string values!");
		return;
	}

	// Concatenate strings
	valueString.erase(valueString.begin());
	valueString.pop_back();
	variable.getValue().setString(variable.getValue().getString() + valueString);
}

bool ScriptInterpreter::_isLocalVariableExisting(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return true;
		}
	}

	return false;
}

ScriptVariable& ScriptInterpreter::_getLocalVariable(const string& variableID)
{
	for (auto& variable : _localVariablesStack.back())
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Local script variable \"" + variableID + "\" not found!");
}

ScriptVariable& ScriptInterpreter::_getGlobalVariable(const string& variableID)
{
	for (auto& variable : _globalVariables)
	{
		if (variableID == variable.getID())
		{
			return variable;
		}
	}

	_fe3d.logger_throwError("Global script variable \"" + variableID + "\" not found!");
}