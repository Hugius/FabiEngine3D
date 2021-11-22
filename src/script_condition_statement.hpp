#pragma once

#include "script_condition_type.hpp"

class ScriptConditionStatement final
{
public:
	ScriptConditionStatement(unsigned int scopeDepth, bool isTrue);

	// VOID
	void setTrue();
	void setFalse();
	void setType(ScriptConditionType type);

	// UNSIGNED INT
	const unsigned int getScopeDepth() const;

	// BOOL
	const bool isTrue() const;
	const bool isFalse() const;

	// Miscellaneous
	const ScriptConditionType getType() const;

private:
	// UNSIGNED INT
	const unsigned int _scopeDepth;

	// BOOL
	bool _conditionResult = false;

	// Miscellaneous
	ScriptConditionType _type = ScriptConditionType::IF;
};