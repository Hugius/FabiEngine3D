#include "script_executor.hpp"

ScriptExecutor::ScriptExecutor(Script& script) :
	_script(script),
	_scriptInterpreter(script)
{

}

void ScriptExecutor::initialize()
{
	_isRunning = true;
	_isInitialized = true;
	_scriptInterpreter.executeInitialization();
}

void ScriptExecutor::update()
{
	if (_isRunning)
	{
		_scriptInterpreter.executeUpdate();
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
	_scriptInterpreter.executeDestruction();
	_isInitialized = false;
	_isRunning = false;
}

bool ScriptExecutor::isScriptEmpty()
{
	return (_script.getScriptFileCount() == 0);
}

bool ScriptExecutor::isInitialized()
{
	return _isInitialized;
}

bool ScriptExecutor::isRunning()
{
	return _isRunning;
}