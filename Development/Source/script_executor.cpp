#include "script_executor.hpp"

ScriptExecutor::ScriptExecutor(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor,
	ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, 
	AudioEditor& audioEditor, EnvironmentEditor& environmentEditor) :
	_fe3d(fe3d),
	_script(script),
	_scriptInterpreter(fe3d, script, sceneEditor, modelEditor, animationEditor, billboardEditor, audioEditor, environmentEditor)
{

}

void ScriptExecutor::load()
{
	// Initialize script execution & run initialization scripts
	_fe3d.misc_showCursor();
	_scriptInterpreter.load();
	_scriptInterpreter.executeInitialization();
	_isInitialized = true;
	_isRunning = true;
	_skipUpdate = true;

	// Check for errors
	_validateExecution();
}

void ScriptExecutor::update(bool debug)
{
	if (_isInitialized && _isRunning)
	{
		// Skip first frame, then update fulltime
		if (!_skipUpdate || debug)
		{
			_scriptInterpreter.executeUpdate(debug);
		}
		else
		{
			_skipUpdate = false;
		}

		// Custom cursor is only enabled in engine preview
		if (!_fe3d.engine_isGameExported())
		{
			_fe3d.guiEntity_hide("@@cursor");
		}

		// Check for errors
		_validateExecution();
	}
}

void ScriptExecutor::unload()
{
	if (_isInitialized)
	{
		// Execute destruction scripts
		_scriptInterpreter.executeDestruction();

		// Unload script execution
		_scriptInterpreter.unload();

		// Miscellaneous
		_fe3d.misc_hideCursor();
		_fe3d.engine_resume(); // Resume engine updates, just in case game was paused while stopping
		_isInitialized = false;
		_isRunning = false;
	}
}

void ScriptExecutor::setCurrentProjectID(const string& projectName)
{
	_scriptInterpreter.setCurrentProjectID(projectName);
}

void ScriptExecutor::pause()
{
	if (_isInitialized && _isRunning)
	{
		// Pause engine updates & script execution
		_wasCursorVisible = _fe3d.misc_isCursorVisible();
		_fe3d.misc_hideCursor();
		_fe3d.audioEntity_pauseAll();
		_fe3d.music_pause();
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
		_fe3d.camera_center();
		_fe3d.audioEntity_resumeAll();
		_fe3d.music_resume();
		_fe3d.engine_resume();
		_isRunning = true;
		_skipUpdate = true;
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
	if (_scriptInterpreter.hasThrownError()) // Script threw an error
	{
		_scriptInterpreter.unload();
		_fe3d.misc_hideCursor();
		_isInitialized = false;
		_isRunning = false;
	}
	else if (_scriptInterpreter.gameMustStop()) // Script must stop
	{
		this->unload();
	}
}