#include "script_variable.hpp"

ScriptVariable::ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, const string& ID, bool constant, ScriptValue value) :
	_fe3d(fe3d),
	_scope(scope),
	_ID(ID),
	_isConstant(constant),
	_value(value)
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

bool ScriptVariable::isConstant()
{
	return _isConstant;
}

void ScriptVariable::changeValue(ScriptValue value)
{
	if (_isConstant)
	{
		_fe3d.logger_throwError("Cannot change script value: variable is constant!");
	}

	_value = value;
}

ScriptValue& ScriptVariable::getValue()
{
	return _value;
}