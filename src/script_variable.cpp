#include "script_variable.hpp"
#include "logger.hpp"

ScriptVariable::ScriptVariable(const string & id, ScriptVariableScope scope, ScriptVariableType type, bool isConstant, const vector<shared_ptr<ScriptValue>> & values)
	:
	_scope(scope),
	_type(type),
	_id(id),
	_isConstant(isConstant)
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

const ScriptVariableScope ScriptVariable::getScope() const
{
	return _scope;
}

const ScriptVariableType ScriptVariable::getType() const
{
	return _type;
}

const bool ScriptVariable::isConstant() const
{
	return _isConstant;
}

void ScriptVariable::setValues(const vector<shared_ptr<ScriptValue>> & values)
{
	_values = values;
}

void ScriptVariable::setValue(shared_ptr<ScriptValue> value, unsigned int index)
{
	if(index >= _values.size())
	{
		abort();
	}

	if(_isConstant)
	{
		abort();
	}

	_values[index] = value;
}

void ScriptVariable::addValue(shared_ptr<ScriptValue> value)
{
	_values.push_back(value);
}

void ScriptVariable::deleteValue(unsigned int index)
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

const shared_ptr<ScriptValue> ScriptVariable::getValue(unsigned int index) const
{
	if(index >= _values.size())
	{
		abort();
	}

	return _values[index];
}

const unsigned int ScriptVariable::getValueCount() const
{
	return static_cast<unsigned int>(_values.size());
}