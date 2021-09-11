#pragma once

#include "script_condition_type.hpp"

class ScriptConditionStatement final
{
public:
	ScriptConditionStatement(unsigned int scopeDepth, bool isTrue);

	// Voids
	void setTrue();
	void setFalse();
	void setType(ScriptConditionType type);

	// Integers
	const unsigned int getScopeDepth();

	// Booleans
	const bool isTrue();
	const bool isFalse();

	// Miscellaneous
	const ScriptConditionType getType();

private:
	// Integers
	const unsigned int _scopeDepth;

	// Booleans
	bool _conditionResult = false;

	// Miscellaneous
	ScriptConditionType _type = ScriptConditionType::IF;
};