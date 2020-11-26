#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableArithmetic(const string& scriptLine)
{
	// Temporary values
	std::istringstream iss(scriptLine);
	string operatorString = "";
	string nameString = "";
	string valueString = "";

	// Extract data
	iss >> operatorString >> nameString >> valueString;

	// Check if valid arithmetic keyword
	if (operatorString != _plusKeyword && operatorString != _minusKeyword && operatorString != _multiplyKeyword && operatorString != _divideKeyword)
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

	// Check if value is not empty
	if (valueString.empty())
	{
		_throwScriptError("no arithmetic value found!");
		return;
	}

	// Execute arithmetic operation
	if ((variable.getValue().getType() == ScriptValueType::INTEGER) && _isIntegerValue(valueString)) // Integer
	{
		// Create value
		auto value = ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(valueString));
		int result = variable.getValue().getInteger();

		// Determine arithmetic type
		if (operatorString == _plusKeyword)
		{
			result += value.getInteger();
		}
		else if (operatorString == _minusKeyword)
		{
			result -= value.getInteger();
		}
		else if (operatorString == _multiplyKeyword)
		{
			result *= value.getInteger();
		}
		else if (operatorString == _divideKeyword)
		{
			result /= value.getInteger();
		}

		// Set resulting value
		variable.getValue().setInteger(result);
	}
	else if ((variable.getValue().getType() == ScriptValueType::DECIMAL) && _isDecimalValue(valueString)) // Decimal
	{
		// Create value
		auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString));
		float result = variable.getValue().getDecimal();

		// Determine arithmetic type
		if (operatorString == _plusKeyword)
		{
			result += value.getDecimal();
		}
		else if (operatorString == _minusKeyword)
		{
			result -= value.getDecimal();
		}
		else if (operatorString == _multiplyKeyword)
		{
			result *= value.getDecimal();
		}
		else if (operatorString == _divideKeyword)
		{
			result /= value.getDecimal();
		}

		// Set resulting value
		variable.getValue().setDecimal(result);
	}
	else if ((variable.getValue().getType() == ScriptValueType::VEC3) && _isDecimalValue(valueString)) // Vec3
	{
		// Create value
		auto value = ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(valueString));
		Vec3 result = variable.getValue().getVec3();

		// Determine arithmetic type
		if (operatorString == _plusKeyword)
		{
			result += value.getDecimal();
		}
		else if (operatorString == _minusKeyword)
		{
			result -= value.getDecimal();
		}
		else if (operatorString == _multiplyKeyword)
		{
			result *= value.getDecimal();
		}
		else if (operatorString == _divideKeyword)
		{
			result /= value.getDecimal();
		}

		// Set resulting value
		variable.getValue().setVec3(result);
	}
	else
	{
		_throwScriptError("invalid arithmetic value!");
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