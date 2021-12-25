#pragma once

#include "script_condition_type.hpp"

class ScriptConditionStatement final
{
public:
	ScriptConditionStatement(unsigned int scopeDepth, bool isTrue);

	void setTrue();
	void setFalse();
	void setType(ScriptConditionType type);

	const unsigned int getScopeDepth() const;

	const bool isTrue() const;
	const bool isFalse() const;

	const ScriptConditionType getType() const;

private:
	const unsigned int _scopeDepth;

	bool _conditionResult = false;

	ScriptConditionType _type = ScriptConditionType::IF;
};