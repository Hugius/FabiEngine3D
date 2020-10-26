#pragma once

#include "fabi_engine_3d.hpp"
#include "script_value_type.hpp"

class ScriptValue final
{
public:
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, const string& value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, float value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, int value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, bool value);

	void operator=(const ScriptValue& other);

	void setString(const string& value);
	void setDecimal(float value);
	void setInteger(int value);
	void setBoolean(bool value);

	ScriptValueType getType();
	const string& getString();
	float getDecimal();
	int getInteger();
	bool getBoolean();

private:
	FabiEngine3D& _fe3d;

	const ScriptValueType _type;

	string _string = "";
	float _decimal = 0.0f;
	int _integer = 0;
	bool _boolean = false;
};