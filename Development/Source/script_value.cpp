#include "script_value.hpp"

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type) :
	_fe3d(fe3d),
	_type(type)
{

}

void ScriptValue::setString(const string& value)
{
	if (_type != ScriptValueType::STRING)
	{
		_fe3d.logger_throwError("Cannot set script value: wrong type!");
	}

	_string = value;
}

void ScriptValue::setDecimal(float value)
{
	if (_type != ScriptValueType::DECIMAL)
	{
		_fe3d.logger_throwError("Cannot set script value: wrong type!");
	}

	_decimal = value;
}

void ScriptValue::setInteger(int value)
{
	if (_type != ScriptValueType::INTEGER)
	{
		_fe3d.logger_throwError("Cannot set script value: wrong type!");
	}

	_integer = value;
}

void ScriptValue::setBoolean(bool value)
{
	if (_type != ScriptValueType::BOOLEAN)
	{
		_fe3d.logger_throwError("Cannot set script value: wrong type!");
	}

	_boolean = value;
}

ScriptValueType ScriptValue::getType()
{
	return _type;
}

const string& ScriptValue::getString()
{
	if (_type != ScriptValueType::STRING)
	{
		_fe3d.logger_throwError("Cannot get script value: wrong type!");
	}

	return _string;
}

float ScriptValue::getDecimal()
{
	if (_type != ScriptValueType::DECIMAL)
	{
		_fe3d.logger_throwError("Cannot get script value: wrong type!");
	}

	return _decimal;
}

int ScriptValue::getInteger()
{
	if (_type != ScriptValueType::INTEGER)
	{
		_fe3d.logger_throwError("Cannot get script value: wrong type!");
	}

	return _integer;
}

bool ScriptValue::getBoolean()
{
	if (_type != ScriptValueType::BOOLEAN)
	{
		_fe3d.logger_throwError("Cannot get script value: wrong type!");
	}

	return _boolean;
}