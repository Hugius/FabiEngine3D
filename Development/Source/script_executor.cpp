#include "script_executor.hpp"

ScriptExecutor::ScriptExecutor(shared_ptr<Script> script) :
	_script(script)
{

}

void ScriptExecutor::initialize()
{
	_isRunning = true;
	_isInitialized = true;
}

void ScriptExecutor::execute()
{
	if (_isRunning)
	{
		_script->execute();
	}
}

void ScriptExecutor::pause()
{
	_isRunning = false;
}

void ScriptExecutor::unpause()
{
	_isRunning = true;
}

void ScriptExecutor::reset()
{
	_script->reset();
	_isInitialized = false;
	_isRunning = false;
}

bool ScriptExecutor::isScriptEmpty()
{
	return (_script->getScriptFileCount() == 0);
}

bool ScriptExecutor::isInitialized()
{
	return _isInitialized;
}

bool ScriptExecutor::isRunning()
{
	return _isRunning;
}