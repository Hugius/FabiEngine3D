#pragma once

#include "script_value.hpp"

struct ScriptVariable
{
	string ID;

	bool constant;

	shared_ptr<ScriptValue> value;
};