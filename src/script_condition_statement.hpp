#pragma once

#include "script_condition_type.hpp"

class ScriptConditionStatement final
{
public:
	ScriptConditionStatement(int scopeDepth, bool isTrue);

	void setTrue();
	void setFalse();
	void setType(ScriptConditionType type);

	const int getScopeDepth() const;

	const bool isTrue() const;
	const bool isFalse() const;

	const ScriptConditionType getType() const;

private:
	const int _scopeDepth;

	bool _conditionResult = false;

	ScriptConditionType _type = ScriptConditionType::IF;
};