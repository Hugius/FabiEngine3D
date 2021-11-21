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

	// Voids
	void setVec3(fvec3 value);
	void setString(const string& value);
	void setDecimal(float value);
	void setInteger(int value);
	void setBoolean(bool value);

	// Strings
	const string& getString() const;

	// Vectors
	fvec3 getVec3() const;

	// Decimals
	float getDecimal() const;

	// Integers
	int getInteger() const;

	// Booleans
	bool getBoolean() const;

	// Miscellaneous
	const ScriptValueType& getType() const;

private:
	// Strings
	string _string = "";

	// Vectors
	fvec3 _vec3 = fvec3(0.0f);

	// Decimals
	float _decimal = 0.0f;

	// Integers
	int _integer = 0;

	// Booleans
	bool _boolean = false;

	// Miscellaneous
	const ScriptValueType _type;
	FabiEngine3D& _fe3d;
};