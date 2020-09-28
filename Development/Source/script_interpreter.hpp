#pragma once

#include "script.hpp"

class ScriptInterpreter
{
public:
	ScriptInterpreter(Script& script);

	void executeInitialization();
	void executeUpdate();
	void executeDestruction();

private:
	Script& _script;

	void _executeInitialization();
	void _executeUpdate();
	void _executeDestruction();
};