#include "script_value.hpp"

ScriptValue::ScriptValue(ScriptValueType type, bool isConstant) :
	_type(type),
	_isConstant(isConstant)
{

}

void ScriptValue::setString(string str)
{
	if (_type == ScriptValueType::STRING && !_isConstant)
	{
		_string = str;
	}
}

void ScriptValue::setBoolean(bool boolean)
{
	if (_type == ScriptValueType::BOOLEAN && !_isConstant)
	{
		_boolean = boolean;
	}
}

void ScriptValue::setNumber(float number)
{
	if (_type == ScriptValueType::NUMBER && !_isConstant)
	{
		_number = number;
	}
}

ScriptValueType ScriptValue::getType()
{
	return _type;
}

string ScriptValue::getString()
{
	return _string;
}

bool ScriptValue::getBoolean()
{
	return _boolean;
}

float ScriptValue::getNumber()
{
	return _number;
}