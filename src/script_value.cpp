#include "script_value.hpp"
#include "logger.hpp"

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type)
	:
	_fe3d(fe3d),
	_type(type)
{

}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, const string& value)
	:
	ScriptValue(fe3d, type)
{
	// Validate type
	if(type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	// Set value
	setString(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, float value)
	:
	ScriptValue(fe3d, type)
{
	// Validate type
	if(type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	// Set value
	setDecimal(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, int value)
	:
	ScriptValue(fe3d, type)
{
	// Validate type
	if(type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	// Set value
	setInteger(value);
}

ScriptValue::ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, bool value)
	:
	ScriptValue(fe3d, type)
{
	// Validate type
	if(type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::ScriptValue");
	}

	// Set value
	setBoolean(value);
}

void ScriptValue::setString(const string& value)
{
	// Validate type
	if(_type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::setString");
	}

	// Set value
	_string = value;
}

void ScriptValue::setDecimal(float value)
{
	// Validate type
	if(_type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::setDecimal");
	}

	// Set value
	_decimal = value;
}

void ScriptValue::setInteger(int value)
{
	// Validate type
	if(_type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::setInteger");
	}

	// Set value
	_integer = value;
}

void ScriptValue::setBoolean(bool value)
{
	// Validate type
	if(_type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::setBoolean");
	}

	// Set value
	_boolean = value;
}

const string& ScriptValue::getString() const
{
	// Validate type
	if(_type != ScriptValueType::STRING)
	{
		Logger::throwError("ScriptValue::getString");
	}

	// Return value
	return _string;
}

const float ScriptValue::getDecimal() const
{
	// Validate type
	if(_type != ScriptValueType::DECIMAL)
	{
		Logger::throwError("ScriptValue::getDecimal");
	}

	// Return value
	return _decimal;
}

const int ScriptValue::getInteger() const
{
	// Validate type
	if(_type != ScriptValueType::INTEGER)
	{
		Logger::throwError("ScriptValue::getInteger");
	}

	// Return value
	return _integer;
}

const bool ScriptValue::getBoolean() const
{
	// Validate type
	if(_type != ScriptValueType::BOOLEAN)
	{
		Logger::throwError("ScriptValue::getBoolean");
	}

	// Return value
	return _boolean;
}

const ScriptValueType& ScriptValue::getType() const
{
	return _type;
}