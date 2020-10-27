#include "script_executor.hpp"

ScriptExecutor::ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor) :
	_fe3d(fe3d),
	_script(script),
	_scriptInterpreter(fe3d, script, sceneEditor)
{

}

void ScriptExecutor::load()
{
	_isRunning = true;
	_isInitialized = true;
	_scriptInterpreter.load();
	_scriptInterpreter.executeInitialization();
	_validateExecution();
}

void ScriptExecutor::update()
{
	if (_isRunning)
	{
		_scriptInterpreter.executeUpdate();
		_validateExecution();
	}
}

void ScriptExecutor::unload()
{
	_scriptInterpreter.executeDestruction();
	_scriptInterpreter.unload();
	_isInitialized = false;
	_isRunning = false;
}

void ScriptExecutor::pause()
{
	_isRunning = false;
}

void ScriptExecutor::unpause()
{
	_isRunning = true;
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

void ScriptExecutor::_validateExecution()
{
	if (_scriptInterpreter.hasThrownError())
	{
		_scriptInterpreter.unload();
		_isInitialized = false;
		_isRunning = false;
	}
}