#include "script_interpreter.hpp"

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