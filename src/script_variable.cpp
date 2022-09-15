#include "script_variable.hpp"

ScriptVariable::ScriptVariable(const string & id, ScriptScopeType scope, ScriptVariableType type, bool isFinal, const vector<shared_ptr<ScriptValue>> & values)
	:
	_scope(scope),
	_type(type),
	_id(id),
	_isFinal(isFinal)
{
	if(_id.empty())
	{
		abort();
	}

	_values = values;
}

const string & ScriptVariable::getId() const
{
	return _id;
}

const ScriptScopeType ScriptVariable::getScope() const
{
	return _scope;
}

const ScriptVariableType ScriptVariable::getType() const
{
	return _type;
}

const bool ScriptVariable::isFinal() const
{
	return _isFinal;
}

void ScriptVariable::setValues(const vector<shared_ptr<ScriptValue>> & values)
{
	_values = values;
}

void ScriptVariable::setValue(shared_ptr<ScriptValue> value, int index)
{
	if(index >= _values.size())
	{
		abort();
	}

	if(_isFinal)
	{
		abort();
	}

	_values[index] = value;
}

void ScriptVariable::addValue(shared_ptr<ScriptValue> value)
{
	_values.push_back(value);
}

void ScriptVariable::deleteValue(int index)
{
	if(index >= _values.size())
	{
		abort();
	}

	_values.erase(_values.begin() + index);
}

void ScriptVariable::deleteValues()
{
	_values.clear();
}

const shared_ptr<ScriptValue> ScriptVariable::getValue(int index) const
{
	if(index >= _values.size())
	{
		abort();
	}

	return _values[index];
}

const int ScriptVariable::getValueCount() const
{
	return static_cast<int>(_values.size());
}