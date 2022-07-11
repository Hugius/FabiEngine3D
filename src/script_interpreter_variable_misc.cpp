#include "script_interpreter.hpp"

void ScriptInterpreter::_processVariableTypecast(const string & scriptLine)
{
	string nameString = "";
	string typeString = "";

	for(const auto & character : scriptLine.substr(CAST_KEYWORD.size() + 1))
	{
		if(character == ' ')
		{
			break;
		}
		else
		{
			nameString += character;
		}
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwRuntimeError("variable \"" + nameString + "\" does not exist");

		return;
	}

	if(scriptLine.size() < (CAST_KEYWORD.size() + nameString.size() + 3))
	{
		_throwRuntimeError("type missing");

		return;
	}

	typeString = scriptLine.substr(CAST_KEYWORD.size() + nameString.size() + 2);

	const auto variable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(variable->getType() == ScriptVariableType::MULTIPLE)
	{
		_throwRuntimeError(LIST_KEYWORD + " variables cannot be typecasted");

		return;
	}

	if(variable->isConstant())
	{
		_throwRuntimeError(CONST_KEYWORD + " variables cannot be typecasted");

		return;
	}

	if((variable->getValue(0)->getType() == ScriptValueType::INTEGER) && (typeString == BOOLEAN_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, static_cast<bool>(variable->getValue(0)->getInteger())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::INTEGER) && (typeString == DECIMAL_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, static_cast<float>(variable->getValue(0)->getInteger())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::INTEGER) && (typeString == STRING_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, to_string(variable->getValue(0)->getInteger())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::DECIMAL) && (typeString == INTEGER_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, static_cast<int>(variable->getValue(0)->getDecimal())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::DECIMAL) && (typeString == STRING_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, to_string(variable->getValue(0)->getDecimal())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::BOOLEAN) && (typeString == INTEGER_KEYWORD))
	{
		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, static_cast<int>(variable->getValue(0)->getBoolean())), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::BOOLEAN) && (typeString == STRING_KEYWORD))
	{
		const auto newValue = variable->getValue(0)->getBoolean() ? "<true>" : "<false>";

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::STRING, newValue), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::STRING) && (typeString == BOOLEAN_KEYWORD))
	{
		if(!_isBooleanValue(variable->getValue(0)->getString()))
		{
			_throwRuntimeError("invalid boolean string");

			return;
		}

		const auto newValue = ((variable->getValue(0)->getString() == "<true>") ? true : false);

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::BOOLEAN, newValue), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::STRING) && (typeString == INTEGER_KEYWORD))
	{
		if(!_isIntegerValue(variable->getValue(0)->getString()))
		{
			_throwRuntimeError("invalid integer string");

			return;
		}

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::INTEGER, stoi(_limitIntegerString(variable->getValue(0)->getString()))), 0);
	}
	else if((variable->getValue(0)->getType() == ScriptValueType::STRING) && (typeString == DECIMAL_KEYWORD))
	{
		if(!_isDecimalValue(variable->getValue(0)->getString()))
		{
			_throwRuntimeError("invalid decimal string");

			return;
		}

		variable->setValue(make_shared<ScriptValue>(ScriptValueType::DECIMAL, stof(_limitDecimalString(variable->getValue(0)->getString()))), 0);
	}
	else
	{
		_throwRuntimeError("invalid casting type");

		return;
	}
}

const bool ScriptInterpreter::_isLocalVariableExisting(const string & variableId)
{
	const auto variables = _localVariables[_executionDepth];

	return (variables.find(variableId) != variables.end());
}

const bool ScriptInterpreter::_isGlobalVariableExisting(const string & variableId) const
{
	return (_globalVariables.find(variableId) != _globalVariables.end());
}

const shared_ptr<ScriptVariable> ScriptInterpreter::_getLocalVariable(const string & variableId)
{
	const auto iterator = _localVariables.at(_executionDepth).find(variableId);

	if(iterator != _localVariables.at(_executionDepth).end())
	{
		return iterator->second;
	}

	abort();
}

const shared_ptr<ScriptVariable> ScriptInterpreter::_getGlobalVariable(const string & variableId) const
{
	const auto iterator = _globalVariables.find(variableId);

	if(iterator != _globalVariables.end())
	{
		return iterator->second;
	}

	abort();
}