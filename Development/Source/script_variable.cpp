#include "script_variable.hpp"

ScriptVariable::ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type, 
	const string& ID, bool constant, vector<ScriptValue> values)
	:
	_fe3d(fe3d),
	_scope(scope),
	_type(type),
	_ID(ID),
	_isConstant(constant),
	_values(values)
{

}

const string& ScriptVariable::getID()
{
	return _ID;
}

ScriptVariableScope ScriptVariable::getScope()
{
	return _scope;
}

ScriptVariableType ScriptVariable::getType()
{
	return _type;
}

bool ScriptVariable::isConstant()
{
	return _isConstant;
}

void ScriptVariable::changeValues(vector<ScriptValue> values)
{
	_values.clear();
	_values = values;
}

void ScriptVariable::changeValue(ScriptValue value, unsigned int index)
{
	// Check if variable is immutable
	if (_isConstant)
	{
		_fe3d.logger_throwError("Cannot change script value: variable is constant!");
	}

	// Delete old value
	_values.erase(_values.begin() + index);
	_values.insert(_values.begin() + index, value);
}

ScriptValue& ScriptVariable::getValue(unsigned int index)
{
	// Validate index
	if (index >= _values.size())
	{
		_fe3d.logger_throwError("Invalid index at script variable!");
	}

	return _values[index];
}

unsigned int ScriptVariable::getValueCount()
{
	return _values.size();
}