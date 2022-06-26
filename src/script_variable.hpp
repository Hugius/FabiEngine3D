#pragma once

#include "script_value.hpp"
#include "script_scope_type.hpp"
#include "script_variable_type.hpp"

class ScriptVariable final
{
public:
	ScriptVariable(const string & id, ScriptScopeType scope, ScriptVariableType type, bool isConstant, const vector<shared_ptr<ScriptValue>> & values);

	void addValue(shared_ptr<ScriptValue> value);
	void setValues(const vector<shared_ptr<ScriptValue>> & values);
	void setValue(shared_ptr<ScriptValue> value, int index);
	void deleteValue(int index);
	void deleteValues();

	const shared_ptr<ScriptValue> getValue(int index) const;

	const string & getId() const;

	const int getValueCount() const;

	const bool isConstant() const;

	const ScriptScopeType getScope() const;
	const ScriptVariableType getType() const;

private:
	const string _id;

	const bool _isConstant;

	const ScriptScopeType _scope;
	const ScriptVariableType _type;

	vector<shared_ptr<ScriptValue>> _values = {};
};