#pragma once

#include "script_value.hpp"

struct ScriptVariable
{
	string ID;

	shared_ptr<ScriptValue> value;
};