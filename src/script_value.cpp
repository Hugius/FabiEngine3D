#include "script_value.hpp"
#include "logger.hpp"

ScriptValue::ScriptValue(ScriptValueType type)
	:
	_type(type)
{

}

ScriptValue::ScriptValue(ScriptValueType type, const string& value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	setString(value);
}

ScriptValue::ScriptValue(ScriptValueType type, float value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	setDecimal(value);
}

ScriptValue::ScriptValue(ScriptValueType type, int value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	setInteger(value);
}

ScriptValue::ScriptValue(ScriptValueType type, bool value)
	:
	ScriptValue(type)
{
	if(type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	setBoolean(value);
}

void ScriptValue::setString(const string& value)
{
	if(_type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::setString");
	}

	_string = value;
}

void ScriptValue::setDecimal(float value)
{
	if(_type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::setDecimal");
	}

	_decimal = value;
}

void ScriptValue::setInteger(int value)
{
	if(_type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::setInteger");
	}

	_integer = value;
}

void ScriptValue::setBoolean(bool value)
{
	if(_type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::setBoolean");
	}

	_boolean = value;
}

const string& ScriptValue::getString() const
{
	if(_type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::getString");
	}

	return _string;
}

const float ScriptValue::getDecimal() const
{
	if(_type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::getDecimal");
	}

	return _decimal;
}

const int ScriptValue::getInteger() const
{
	if(_type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::getInteger");
	}

	return _integer;
}

const bool ScriptValue::getBoolean() const
{
	if(_type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::getBoolean");
	}

	return _boolean;
}

const ScriptValueType& ScriptValue::getType() const
{
	return _type;
}