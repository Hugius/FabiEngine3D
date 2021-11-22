#pragma once

#include "fe3d.hpp"
#include "script_value_type.hpp"

class ScriptValue final
{
public:
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, fvec3 value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, const string& value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, float value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, int value);
	ScriptValue(FabiEngine3D& fe3d, ScriptValueType type, bool value);

	// VOID
	void setVec3(fvec3 value);
	void setString(const string& value);
	void setDecimal(float value);
	void setInteger(int value);
	void setBoolean(bool value);

	// STRING
	const string& getString() const;

	// FVEC3
	fvec3 getVec3() const;

	// FLOAT
	float getDecimal() const;

	// INT
	int getInteger() const;

	// BOOL
	bool getBoolean() const;

	// Miscellaneous
	const ScriptValueType& getType() const;

private:
	// STRING
	string _string = "";

	// FVEC3
	fvec3 _vec3 = fvec3(0.0f);

	// FLOAT
	float _decimal = 0.0f;

	// INT
	int _integer = 0;

	// BOOL
	bool _boolean = false;

	// Miscellaneous
	const ScriptValueType _type;
	FabiEngine3D& _fe3d;
};