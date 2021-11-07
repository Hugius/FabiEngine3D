#include "script_value.hpp"
#include "logger.hpp"

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type)
	:
	_fe3d(fe3d),
	_type(type)
{

}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, Vec3 value)
	:
	ScriptValue(fe3d, type)
{
	setVec3(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, const string& value)
	:
	ScriptValue(fe3d, type)
{
	setString(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, float value)
	:
	ScriptValue(fe3d, type)
{
	setDecimal(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, int value)
	:
	ScriptValue(fe3d, type)
{
	setInteger(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, bool value)
	:
	ScriptValue(fe3d, type)
{
	setBoolean(value);
}

void ScriptValue::setVec3(Vec3 value)
{
	_vec3 = value;
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

const ScriptValueType& ScriptValue::getType() const
{
	return _type;
}

Vec3 ScriptValue::getVec3() const
{
	return _vec3;
}

const string& ScriptValue::getString() const
{
	if(_type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::getString");
	}

	return _string;
}

float ScriptValue::getDecimal() const
{
	if(_type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::getDecimal");
	}

	return _decimal;
}

int ScriptValue::getInteger() const
{
	if(_type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::getInteger");
	}

	return _integer;
}

bool ScriptValue::getBoolean() const
{
	if(_type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::getBoolean");
	}

	return _boolean;
}