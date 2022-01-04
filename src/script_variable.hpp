#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type, const string& ID, bool constant, vector<ScriptValue> values);

	void addValue(ScriptValue value);
	void setValues(vector<ScriptValue> values);
	void setValue(ScriptValue value, unsigned int index = 0);
	void deleteValue(unsigned int index);
	void deleteValues();

	const string& getID() const;

	const unsigned int getValueCount() const;

	const bool isConstant() const;

	ScriptValue& getValue(unsigned int index = 0) const;
	const ScriptVariableScope getScope() const;
	const ScriptVariableType getType() const;

private:
	string _ID;

	bool _isConstant;

	vector<shared_ptr<ScriptValue>> _values;
	ScriptVariableScope _scope;
	ScriptVariableType _type;
	FabiEngine3D& _fe3d;
};