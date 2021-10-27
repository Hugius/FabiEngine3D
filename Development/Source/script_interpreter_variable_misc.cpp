#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableTypecast(const string& scriptLine)
{
	// Temporary values
	string nameString = "";
	string typeString = "";

	// Extract name
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

	// Check if variable exists
	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable not existing!");
		return;
	}

	// Check if type is present
	if(scriptLine.size() >= (CASTING_KEYWORD.size() + nameString.size() + 3))
	{
		// Extract remaining text (type)
		typeString = scriptLine.substr(CASTING_KEYWORD.size() + nameString.size() + 2);
	}
	else
	{
		_throwScriptError("type missing!");
		return;
	}

	// Retrieve variable
	auto& variable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	// Check if variable is not a list
	if(variable.getType() == ScriptVariableType::MULTIPLE)
	{
		_throwScriptError("list variables cannot be typecasted!");
		return;
	}

	// Check if variable can be changed
	if(variable.isConstant())
	{
		_throwScriptError("constant variables cannot be typecasted!");
		return;
	}

	// Determine to which new type the variable must cast
	if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == DECIMAL_KEYWORD)) // From INT to DEC
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, static_cast<float>(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == BOOLEAN_KEYWORD)) // From INT to BOOL
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, static_cast<bool>(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::INTEGER) && (typeString == STRING_KEYWORD)) // From INT to STR
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getInteger())));
	}
	else if((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == INTEGER_KEYWORD)) // From DEC to INT
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getDecimal())));
	}
	else if((variable.getValue().getType() == ScriptValueType::DECIMAL) && (typeString == STRING_KEYWORD)) // From DEC to STR
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(variable.getValue().getDecimal())));
	}
	else if((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == INTEGER_KEYWORD)) // From BOOL to INT
	{
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(variable.getValue().getBoolean())));
	}
	else if((variable.getValue().getType() == ScriptValueType::BOOLEAN) && (typeString == STRING_KEYWORD)) // From BOOL to STR
	{
		string newValue = variable.getValue().getBoolean() ? "<true>" : "<false>";
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, newValue));
	}
	else if((variable.getValue().getType() == ScriptValueType::VEC3) && (typeString == STRING_KEYWORD)) // From VEC3 to STR
	{
		string newValue = "[" +
			to_string(variable.getValue().getVec3().x) + " " +
			to_string(variable.getValue().getVec3().y) + " " +
			to_string(variable.getValue().getVec3().z) + "]";
		variable.changeValue(ScriptValue(_fe3d, ScriptValueType::STRING, newValue));
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == BOOLEAN_KEYWORD)) // From STR to BOOL
	{
		// Check if string can be casted
		if(_isBooleanValue(variable.getValue().getString()))
		{
			bool newValue = (variable.getValue().getString() == "<true>") ? true : false;
			variable.changeValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, newValue));
		}
		else
		{
			_throwScriptError("variable cannot be typecasted to boolean: invalid string!");
			return;
		}
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == INTEGER_KEYWORD)) // From STR to INT
	{
		// Check if string can be casted
		if(_isIntegerValue(variable.getValue().getString()))
		{
			variable.changeValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(variable.getValue().getString()))));
		}
		else
		{
			_throwScriptError("variable cannot be typecasted to integer: invalid string!");
			return;
		}
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == DECIMAL_KEYWORD)) // From STR to DEC
	{
		// Check if string can be casted
		if(_isDecimalValue(variable.getValue().getString()))
		{
			variable.changeValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(variable.getValue().getString()))));
		}
		else
		{
			_throwScriptError("variable cannot be typecasted to decimal: invalid string!");
			return;
		}
	}
	else if((variable.getValue().getType() == ScriptValueType::STRING) && (typeString == VEC3_KEYWORD)) // From STR to VEC3
	{
		// Check if string can be casted
		if(_isVec3Value(variable.getValue().getString()))
		{
			variable.changeValue(ScriptValue(_fe3d, ScriptValueType::VEC3, _extractVec3FromString(variable.getValue().getString())));
		}
		else
		{
			_throwScriptError("variable cannot be typecasted to vec3: invalid string!");
			return;
		}
	}
	else
	{
		_throwScriptError("variable cannot be typecasted: wrong type!");
		return;
	}
}

bool ScriptInterpreter::_isLocalVariableExisting(const string& variableID)
{
	auto& variables = _localVariables[_executionDepth];
	return (variables.find(variableID) != variables.end());
}

bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableID)
{
	return (_globalVariables.find(variableID) != _globalVariables.end());
}

ScriptVariable& ScriptInterpreter::_getLocalVariable(const string& variableID)
{
	auto& variables = _localVariables[_executionDepth];
	auto it = variables.find(variableID);

	if(it != variables.end())
	{
		return it->second;
	}


	Logger::throwError("ScriptInterpreter::_getLocalVariable");
}

ScriptVariable& ScriptInterpreter::_getGlobalVariable(const string& variableID)
{
	auto it = _globalVariables.find(variableID);

	if(it != _globalVariables.end())
	{
		return it->second;
	}

	Logger::throwError("ScriptInterpreter::_getGlobalVariable");
}