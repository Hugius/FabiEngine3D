#pragma once

#include "script_condition_type.hpp"

struct ScriptConditionStatement final
{
	ScriptConditionStatement(unsigned int scopeDepth, bool conditionResult) :
		scopeDepth(scopeDepth),
		conditionResult(conditionResult),
		type(ScriptConditionType::IF)
	{

	}

	const unsigned int scopeDepth;

	bool conditionResult;

	ScriptConditionType type;
};