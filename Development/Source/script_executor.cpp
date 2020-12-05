#include "script_executor.hpp"

ScriptExecutor::ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor, AnimationEditor& animationEditor) :
	_fe3d(fe3d),
	_script(script),
	_scriptInterpreter(fe3d, script, sceneEditor, animationEditor)
{

}

void ScriptExecutor::load()
{
	_fe3d.misc_showCursor();
	_scriptInterpreter.load();
	_scriptInterpreter.executeInitialization();
	_isInitialized = true;
	_isRunning = true;
	_validateExecution();
}

void ScriptExecutor::update()
{
	if (_isInitialized && _isRunning)
	{
		_scriptInterpreter.executeUpdate();
		_fe3d.guiEntity_hide("@@cursor");
		_validateExecution();
	}
}

void ScriptExecutor::unload()
{
	if (_isInitialized)
	{
		_scriptInterpreter.executeDestruction();
		_scriptInterpreter.unload();
		_fe3d.misc_hideCursor();
		_fe3d.engine_resume();
		_isInitialized = false;
		_isRunning = false;
	}
}

void ScriptExecutor::pause()
{
	if (_isInitialized && _isRunning)
	{
		_wasCursorVisible = _fe3d.misc_isCursorVisible();
		_fe3d.misc_hideCursor();
		_fe3d.audioEntity_pauseAll();
		_fe3d.engine_pause();
		_isRunning = false;
	}
}

void ScriptExecutor::unpause()
{
	if (_isInitialized && !_isRunning)
	{
		// Reset cursor
		if (_wasCursorVisible)
		{
			_fe3d.misc_showCursor();
		}

		// Resume game logic
		_fe3d.audioEntity_resumeAll();
		_fe3d.engine_resume();
		_isRunning = true;
	}
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