#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type, const string& ID, bool constant, vector<ScriptValue> values);

	// Voids
	void changeValues(vector<ScriptValue> values);
	void changeValue(ScriptValue value, unsigned int index = 0);
	void addValue(ScriptValue value);
	void removeValue(unsigned int index);

	// Strings
	const string& getID();

	// Integers
	unsigned int getValueCount();

	// Booleans
	bool isConstant();

	// Miscellaneous
	vector<shared_ptr<ScriptValue>>& getValues();
	ScriptValue& getValue(unsigned int index = 0);
	ScriptVariableScope getScope();
	ScriptVariableType getType();

private:
	// Strings
	string _ID;

	// Booleans
	const bool _isConstant;

	// Miscellaneous
	vector<shared_ptr<ScriptValue>> _values;
	ScriptVariableScope _scope;
	ScriptVariableType _type;
	FabiEngine3D& _fe3d;
};