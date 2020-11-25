#include "script_variable.hpp"

ScriptVariable::ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, const string& ID, bool constant, ScriptValue value) :
	_fe3d(fe3d),
	_scope(scope),
	_ID(ID),
	_isConstant(constant)
{
	_value = new ScriptValue(_fe3d, value.getType());

	// Set new value
	if (_value->getType() == ScriptValueType::STRING)
	{
		_value->setString(value.getString());
	}
	else if (_value->getType() == ScriptValueType::DECIMAL)
	{
		_value->setDecimal(value.getDecimal());
	}
	else if (_value->getType() == ScriptValueType::INTEGER)
	{
		_value->setInteger(value.getInteger());
	}
	else if (_value->getType() == ScriptValueType::BOOLEAN)
	{
		_value->setBoolean(value.getBoolean());
	}
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

	// Delete old value
	delete _value;

	// Set new value
	_value = new ScriptValue(_fe3d, value.getType());
	if (_value->getType() == ScriptValueType::STRING)
	{
		_value->setString(value.getString());
	}
	else if (_value->getType() == ScriptValueType::DECIMAL)
	{
		_value->setDecimal(value.getDecimal());
	}
	else if (_value->getType() == ScriptValueType::INTEGER)
	{
		_value->setInteger(value.getInteger());
	}
	else if (_value->getType() == ScriptValueType::BOOLEAN)
	{
		_value->setBoolean(value.getBoolean());
	}
}

ScriptValue& ScriptVariable::getValue()
{
	return *_value;
}