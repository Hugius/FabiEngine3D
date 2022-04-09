#include "script_value.hpp"

ScriptValue::ScriptValue(ScriptValueType type)
	:
	_type(type)
{

}

ScriptValue::ScriptValue(ScriptValueType type, const string & value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::STRING)
	{
		abort();
	}

	setString(value);
}

ScriptValue::ScriptValue(ScriptValueType type, float value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::DECIMAL)
	{
		abort();
	}

	setDecimal(value);
}

ScriptValue::ScriptValue(ScriptValueType type, int value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::INTEGER)
	{
		abort();
	}

	setInteger(value);
}

ScriptValue::ScriptValue(ScriptValueType type, bool value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::BOOLEAN)
	{
		abort();
	}

	setBoolean(value);
}

void ScriptValue::setString(const string & value)
{
	if(_type != ScriptValueType::STRING)
	{
		abort();
	}

	_string = value;
}

void ScriptValue::setDecimal(float value)
{
	if(_type != ScriptValueType::DECIMAL)
	{
		abort();
	}

	_decimal = value;
}

void ScriptValue::setInteger(int value)
{
	if(_type != ScriptValueType::INTEGER)
	{
		abort();
	}

	_integer = value;
}

void ScriptValue::setBoolean(bool value)
{
	if(_type != ScriptValueType::BOOLEAN)
	{
		abort();
	}

	_boolean = value;
}

const string & ScriptValue::getString() const
{
	if(_type != ScriptValueType::STRING)
	{
		abort();
	}

	return _string;
}

const float ScriptValue::getDecimal() const
{
	if(_type != ScriptValueType::DECIMAL)
	{
		abort();
	}

	return _decimal;
}

const int ScriptValue::getInteger() const
{
	if(_type != ScriptValueType::INTEGER)
	{
		abort();
	}

	return _integer;
}

const bool ScriptValue::getBoolean() const
{
	if(_type != ScriptValueType::BOOLEAN)
	{
		abort();
	}

	return _boolean;
}

const ScriptValueType & ScriptValue::getType() const
{
	return _type;
}