#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type, const string& ID, bool constant, vector<ScriptValue> values);

	const string& getID();
	ScriptVariableScope getScope();
	ScriptVariableType getType();
	bool isConstant();
	ScriptValue& getValue(unsigned int index = 0);
	unsigned int getValueCount();

	void changeValues(vector<ScriptValue> values);
	void changeValue(ScriptValue value, unsigned int index = 0);
	void addValue(ScriptValue value);
	void removeValue(unsigned int index);

private:
	FabiEngine3D& _fe3d;

	ScriptVariableScope _scope;
	ScriptVariableType _type;

	string _ID;

	const bool _isConstant;

	vector<shared_ptr<ScriptValue>> _values;
};