#include "script_variable.hpp"
#include "logger.hpp"

ScriptVariable::ScriptVariable(const string& id, ScriptVariableScope scope, ScriptVariableType type, bool isConstant, const vector<ScriptValue>& values)
	:
	_scope(scope),
	_type(type),
	_id(id),
	_isConstant(isConstant)
{
	for(const auto& value : values)
	{
		_values.push_back(make_shared<ScriptValue>(value));
	}
}

const string& ScriptVariable::getId() const
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

void ScriptVariable::setValues(vector<ScriptValue> values)
{
	_values.clear();

	for(const auto& value : values)
	{
		_values.push_back(make_shared<ScriptValue>(value));
	}
}

void ScriptVariable::setValue(ScriptValue value, unsigned int index)
{
	if(_isConstant)
	{
		Logger::throwError("ScriptVariable::changeValue");
	}

	_values.erase(_values.begin() + index);

	_values.insert(_values.begin() + index, make_shared<ScriptValue>(value));
}

void ScriptVariable::addValue(ScriptValue value)
{
	_values.push_back(make_shared<ScriptValue>(value));
}

void ScriptVariable::deleteValue(unsigned int index)
{
	_values.erase(_values.begin() + index);
}

void ScriptVariable::deleteValues()
{
	_values.clear();
}

ScriptValue& ScriptVariable::getValue(unsigned int index) const
{
	if(index >= _values.size())
	{
		Logger::throwError("ScriptVariable::getValue");
	}

	return *_values[index];
}

const unsigned int ScriptVariable::getValueCount() const
{
	return static_cast<unsigned int>(_values.size());
}