#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type, const string& ID, bool constant, vector<ScriptValue> values);

	// VOID
	void changeValues(vector<ScriptValue> values);
	void changeValue(ScriptValue value, unsigned int index = 0);
	void addValue(ScriptValue value);
	void removeValue(unsigned int index);

	// STRING
	const string& getID() const;

	// UNSIGNED INT
	const unsigned int getValueCount() const;

	// BOOL
	const bool isConstant() const;

	// MISCELLANEOUS
	const vector<shared_ptr<ScriptValue>>& getValues() const;
	ScriptValue& getValue(unsigned int index = 0) const;
	const ScriptVariableScope getScope() const;
	const ScriptVariableType getType() const;

private:
	// STRING
	string _ID;

	// BOOL
	const bool _isConstant;

	// MISCELLANEOUS
	vector<shared_ptr<ScriptValue>> _values;
	ScriptVariableScope _scope;
	ScriptVariableType _type;
	FabiEngine3D& _fe3d;
};