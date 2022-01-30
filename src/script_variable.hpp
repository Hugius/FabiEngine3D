#pragma once

#include "script_value.hpp"
#include "script_variable_scope.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(const string& id, ScriptVariableScope scope, ScriptVariableType type, bool isConstant, const vector<shared_ptr<ScriptValue>>& values);

	void addValue(shared_ptr<ScriptValue> value);
	void setValues(const vector<shared_ptr<ScriptValue>>& values);
	void setValue(shared_ptr<ScriptValue> value, unsigned int index = 0);
	void deleteValue(unsigned int index);
	void deleteValues();

	const string& getId() const;

	const unsigned int getValueCount() const;

	const bool isConstant() const;

	shared_ptr<ScriptValue> getValue(unsigned int index = 0) const;
	const ScriptVariableScope getScope() const;
	const ScriptVariableType getType() const;

private:
	string _id;

	bool _isConstant;

	vector<shared_ptr<ScriptValue>> _values;
	ScriptVariableScope _scope;
	ScriptVariableType _type;
};