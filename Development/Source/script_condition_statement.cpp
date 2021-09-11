#include "script_condition_statement.hpp"

ScriptConditionStatement::ScriptConditionStatement(unsigned int scopeDepth, bool isTrue) :
	_scopeDepth(scopeDepth),
	_conditionResult(isTrue)
{

}

void ScriptConditionStatement::setTrue()
{
	_conditionResult = true;
}

void ScriptConditionStatement::setFalse()
{
	_conditionResult = false;
}

void ScriptConditionStatement::setType(ScriptConditionType type)
{
	_type = type;
}

const unsigned int ScriptConditionStatement::getScopeDepth()
{
	return _scopeDepth;
}

const bool ScriptConditionStatement::isTrue()
{
	return _conditionResult;
}

const bool ScriptConditionStatement::isFalse()
{
	return !_conditionResult;
}

const ScriptConditionType ScriptConditionStatement::getType()
{
	return _type;
}