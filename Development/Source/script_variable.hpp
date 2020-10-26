#pragma once

#include "script_value.hpp"
#include "script_variable_type.hpp"

class ScriptVariable
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableType type, const string& ID, bool constant, ScriptValue value);

	const string& getID();
	ScriptVariableType getType();
	bool isConstant();
	ScriptValue& getValue();

	void changeValue(ScriptValue value);

private:
	FabiEngine3D& _fe3d;

	ScriptVariableType _type;

	const string& _ID;

	const bool _isConstant;

	ScriptValue _value;
};