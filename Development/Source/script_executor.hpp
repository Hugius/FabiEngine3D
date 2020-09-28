#pragma once

#include "script_interpreter.hpp"

class ScriptExecutor
{
public:
	ScriptExecutor(Script& script);

	void initialize();
	void update();
	void pause();
	void unpause();
	void reset();

	bool isScriptEmpty();
	bool isInitialized();
	bool isRunning();

private:
	Script& _script;
	ScriptInterpreter _scriptInterpreter;

	bool _isInitialized = false;
	bool _isRunning = false;
};