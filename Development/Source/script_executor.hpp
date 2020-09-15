#pragma once

#include "script.hpp"

class ScriptExecutor
{
public:
	ScriptExecutor(shared_ptr<Script> script);

	void initialize();
	void execute();
	void pause();
	void unpause();
	void reset();

	bool isScriptEmpty();
	bool isInitialized();
	bool isRunning();

private:
	shared_ptr<Script> _script = nullptr;

	bool _isInitialized = false;
	bool _isRunning = false;
};