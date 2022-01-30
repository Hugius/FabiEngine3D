#include "script_interpreter.hpp"
#include "logger.hpp"

void ScriptInterpreter::_processVariableTypecast(const string& scriptLine)
{
	string nameString = "";
	string typeString = "";

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

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("variable \"" + nameString + "\" not existing!");
		return;
	}

	if(scriptLine.size() < (CASTING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwScriptError("type missing!");
		return;
	}

	typeString = scriptLine.substr(CASTING_KEYWORD.size() + nameString.size() + 2);

	const auto variable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(variable->getType() == ScriptVariableType::MULTIPLE)
	{
		_throwScriptError("LIST variables cannot be typecasted!");
		return;
	}

	if(variable->isConstant())
	{
		_throwScriptError("CONST variables cannot be typecasted!");
		return;
	}

	if((variable->getValue()->getType() == ScriptValueType::INTEGER) && (typeString == BOOLEAN_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, static_cast<bool>(variable->getValue()->getInteger())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::INTEGER) && (typeString == DECIMAL_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, static_cast<float>(variable->getValue()->getInteger())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::INTEGER) && (typeString == STRING_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, to_string(variable->getValue()->getInteger())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::DECIMAL) && (typeString == INTEGER_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, static_cast<int>(variable->getValue()->getDecimal())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::DECIMAL) && (typeString == STRING_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, to_string(variable->getValue()->getDecimal())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::BOOLEAN) && (typeString == INTEGER_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, static_cast<int>(variable->getValue()->getBoolean())));
	}
	else if((variable->getValue()->getType() == ScriptValueType::BOOLEAN) && (typeString == STRING_KEYWORD))
	{
		string newValue = variable->getValue()->getBoolean() ? "<true>" : "<false>";
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, newValue));
	}
	else if((variable->getValue()->getType() == ScriptValueType::STRING) && (typeString == BOOLEAN_KEYWORD))
	{
		if(!_isBooleanValue(variable->getValue()->getString()))
		{
			_throwScriptError("invalid boolean string!");
			return;
		}

		bool newValue = (variable->getValue()->getString() == "<true>") ? true : false;
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, newValue));
	}
	else if((variable->getValue()->getType() == ScriptValueType::STRING) && (typeString == INTEGER_KEYWORD))
	{
		if(!_isIntegerValue(variable->getValue()->getString()))
		{
			_throwScriptError("invalid integer string!");
			return;
		}

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(variable->getValue()->getString()))));
	}
	else if((variable->getValue()->getType() == ScriptValueType::STRING) && (typeString == DECIMAL_KEYWORD))
	{
		if(!_isDecimalValue(variable->getValue()->getString()))
		{
			_throwScriptError("invalid decimal string!");
			return;
		}

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(variable->getValue()->getString()))));
	}
	else
	{
		_throwScriptError("invalid casting type!");
		return;
	}
}

const bool ScriptInterpreter::_isLocalVariableExisting(const string& variableId)
{
	const auto variables = _localVariables[_executionDepth];

	return (variables.find(variableId) != variables.end());
}

const bool ScriptInterpreter::_isGlobalVariableExisting(const string& variableId) const
{
	return (_globalVariables.find(variableId) != _globalVariables.end());
}

shared_ptr<ScriptVariable> ScriptInterpreter::_getLocalVariable(const string& variableId)
{
	auto& variables = _localVariables[_executionDepth];
	auto iterator = variables.find(variableId);

	if(iterator != variables.end())
	{
		return iterator->second;
	}

	abort();
}

shared_ptr<ScriptVariable> ScriptInterpreter::_getGlobalVariable(const string& variableId)
{
	auto iterator = _globalVariables.find(variableId);

	if(iterator != _globalVariables.end())
	{
		return iterator->second;
	}

	abort();
}