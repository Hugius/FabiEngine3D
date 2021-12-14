#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableTypecast(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string typeString = "";

	// Extract variable name
	for(const auto& c : scriptLine.substr(CASTING_KEYWORD.size() + 1))
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

	// Check if variable not existing
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	// Check if type is missing
	if(scriptLine.size() < (CASTING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwScriptError("type missing!");
		return;
	}

	// Extract new variable type
	typeString = scriptLine.substr(CASTING_KEYWORD.size() + nameString.size() + 2);

	// Retrieve variable
	auto& variable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if variable is a list
	if(variable.getType() == ScriptVariableType::MULTIPLE)
	{
		_throwScriptError("LIST variables cannot be typecasted!");
		return;
	}

	// Check if variable is constant
	if(variable.isConstant())
	{
		_throwScriptError("CONST variables cannot be typecasted!");
		return;
	}

	// Determine new type
	if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == BOOLEAN_KEYWORD)) // From INT to BOOL
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, static_cast<bool>(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == DECIMAL_KEYWORD)) // From INT to DEC
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, static_cast<float>(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == STRING_KEYWORD)) // From INT to STR
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == INTEGER_KEYWORD)) // From DEC to INT
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getDecimal())));
	}
	else if((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == STRING_KEYWORD)) // From DEC to STR
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getDecimal())));
	}
	else if((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == INTEGER_KEYWORD)) // From BOOL to INT
	{
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getBoolean())));
	}
	else if((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == STRING_KEYWORD)) // From BOOL to STR
	{
		string newValue = variable.getValue().getBoolean() ? "<true>" : "<false>";
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::STRING, newValue));
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == BOOLEAN_KEYWORD)) // From STR to BOOL
	{
		// Check if string invalid
		if(!_isBooleanValue(variable.getValue().getString()))
		{
			_throwScriptError("invalid boolean string!");
			return;
		}

		// Cast to boolean
		bool newValue = (variable.getValue().getString() == "<true>") ? true : false;
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, newValue));
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == INTEGER_KEYWORD)) // From STR to INT
	{
		// Check if string invalid
		if(!_isIntegerValue(variable.getValue().getString()))
		{
			_throwScriptError("invalid integer string!");
			return;
		}

		// Cast to integer
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(variable.getValue().getString()))));
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == DECIMAL_KEYWORD)) // From STR to DEC
	{
		// Check if string invalid
		if(!_isDecimalValue(variable.getValue().getString()))
		{
			_throwScriptError("invalid decimal string!");
			return;
		}

		// Cast to decimal
		variable.setValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(variable.getValue().getString()))));
	}
	else
	{
		_throwScriptError("invalid casting type!");
		return;
	}
}

const bool ScriptInterpreter::_isLocalVariableExisting(const string& variableID)
{
	auto& variables = _localVariables[_executionDepth];

	return (variables.find(variableID) != variables.end());
}

const bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableID) const
{
	return (_globalVariables.find(variableID) != _globalVariables.end());
}

ScriptVariable& ScriptInterpreter::_getLocalVariable(const string& variableID)
{
	auto& variables = _localVariables[_executionDepth];
	auto iterator = variables.find(variableID);

	if(iterator != variables.end())
	{
		return iterator->second;
	}

	Logger::throwError("ScriptInterpreter::_getLocalVariable");
}

ScriptVariable& ScriptInterpreter::_getGlobalVariable(const string& variableID)
{
	auto iterator = _globalVariables.find(variableID);

	if(iterator != _globalVariables.end())
	{
		return iterator->second;
	}

	Logger::throwError("ScriptInterpreter::_getGlobalVariable");
}