#pragma once

#include "fe3d.hpp"
#include "script_value_type.hpp"

class ScriptValue final
{
public:
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, const string& value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, float value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, int value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, bool value);

	// VOID
	void setString(const string& value);
	void setDecimal(float value);
	void setInteger(int value);
	void setBoolean(bool value);

	// STRING
	const string& getString() const;

	// FLOAT
	float getDecimal() const;

	// INT
	int getInteger() const;

	// BOOL
	bool getBoolean() const;

	// MISCELLANEOUS
	const ScriptValueType& getType() const;

private:
	// STRING
	string _string = "";

	// FLOAT
	float _decimal = 0.0f;

	// INT
	int _integer = 0;

	// BOOL
	bool _boolean = false;

	// MISCELLANEOUS
	const ScriptValueType _type;
	FabiEngine3D& _fe3d;
};