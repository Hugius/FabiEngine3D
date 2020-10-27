#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"

class ScriptVariable
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, const string& ID, bool constant, ScriptValue value);

	const string& getID();
	ScriptVariableScope getScope();
	bool isConstant();
	ScriptValue& getValue();

	void changeValue(ScriptValue value);

private:
	FabiEngine3D& _fe3d;

	ScriptVariableScope _scope;

	string _ID;

	const bool _isConstant;

	ScriptValue _value;
};