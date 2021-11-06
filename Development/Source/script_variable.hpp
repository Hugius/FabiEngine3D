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
	const string& getID() const;

	// Integers
	const unsigned int getValueCount() const;

	// Booleans
	const bool isConstant() const;

	// Miscellaneous
	const vector<shared_ptr<ScriptValue>>& getValues() const;
	ScriptValue& getValue(unsigned int index = 0) const;
	const ScriptVariableScope getScope() const;
	const ScriptVariableType getType() const;

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