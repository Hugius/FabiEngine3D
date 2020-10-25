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

void ScriptExecutor::unload()
{
	_scriptInterpreter.executeDestruction();
	_scriptInterpreter.unload();
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