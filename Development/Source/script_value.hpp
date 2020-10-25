#pragma once

#include "fabi_engine_3d.hpp"
#include "script_value_type.hpp"

class ScriptValue final
{
public:
	template<typename T> ScriptValue(ScriptValueType type, T value) :
		_type(type)
	{
		this->setValue(value);
	}

	ScriptValueType getType();

	void setValue(string value)
	{
		_string = value;
	}

	void setValue(float value)
	{
		_decimal = value;
	}

	void setValue(int value)
	{
		_integer = value;
	}

	void setValue(bool value)
	{
		_boolean = value;
	}

	template<typename T> T getValue();

private:
	const ScriptValueType _type;

	string _string = "";
	float _decimal = 0.0f;
	int _integer = 0;
	bool _boolean = false;
};

template<typename T>
inline T ScriptValue::getValue()
{
	switch (_type)
	{
		case ScriptValueType::STRING:
		{
			return _string;
			break;
		}
		case ScriptValueType::DECIMAL:
		{
			return _decimal;
			break;
		}
		case ScriptValueType::INTEGER:
		{
			return _integer;
			break;
		}
		case ScriptValueType::BOOLEAN:
		{
			return _boolean;
			break;
		}
	}
}