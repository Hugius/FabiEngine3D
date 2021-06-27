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
	// Start script execution & run initialization scripts
	_scriptInterpreter.load();
	_scriptInterpreter.executeInitialization();
	_isStarted = true;
	_isRunning = true;
	_mustSkipUpdate = true;

	// Check for errors
	_validateExecution();
}

void ScriptExecutor::update(bool debug)
{
	if (_isStarted && _isRunning)
	{
		// Skip first frame, then update fulltime
		if (!_mustSkipUpdate || debug)
		{
			_scriptInterpreter.executeUpdate(debug);
		}
		else
		{
			_mustSkipUpdate = false;
		}

		// Custom cursor is only enabled in engine preview
		if (!_fe3d.application_isExported())
		{
			// Custom cursor must be inside of viewport or PC cursor must be visible
			if (_fe3d.misc_isCursorInsideViewport() || _fe3d.misc_isCursorVisible())
			{
				_fe3d.imageEntity_hide("@@cursor");
			}
		}

		// Check for errors
		_validateExecution();
	}
}

void ScriptExecutor::pause()
{
	if (_isStarted && _isRunning)
	{
		// Save cursor state
		_wasCursorVisible = _fe3d.misc_isCursorVisible();
		_fe3d.misc_hideCursor();

		// Save timer state
		_wasMillisecondTimerStarted = _fe3d.misc_isMillisecondTimerStarted();
		if (_wasMillisecondTimerStarted)
		{
			_fe3d.misc_stopMillisecondTimer();
		}

		// Save sound states
		for (const auto& soundID : _fe3d.soundEntity_getAllIDs())
		{
			if (_fe3d.soundEntity_isPaused(soundID))
			{
				_pausedSoundIDs.push_back(soundID);
			}
		}

		// Pause sounds
		_fe3d.soundEntity_pauseAll();

		// Save music state
		_wasMusicPaused = _fe3d.music_isPaused();

		// Pause music
		if (_fe3d.music_isPlaying())
		{
			_fe3d.music_pause();
		}

		// Pause engine updates & script execution
		_fe3d.application_pause();
		_isRunning = false;
	}
}

void ScriptExecutor::resume()
{
	if (_isStarted && !_isRunning)
	{
		// Reset cursor
		_fe3d.misc_centerCursor();
		if (_wasCursorVisible)
		{
			_fe3d.misc_showCursor();
		}

		// Reset millisecond timer
		if (_wasMillisecondTimerStarted)
		{
			_fe3d.misc_startMillisecondTimer();
		}

		// Reset sounds
		_fe3d.soundEntity_resumeAll();
		for (const auto& soundID : _pausedSoundIDs)
		{
			_fe3d.soundEntity_pause(soundID);
		}

		// Reset music
		if (_fe3d.music_isPaused() && !_wasMusicPaused)
		{
			_fe3d.music_resume();
		}

		// Resume game logic
		_fe3d.application_resume();
		_isRunning = true;
		_mustSkipUpdate = true;
	}
}

void ScriptExecutor::unload()
{
	if (_isStarted)
	{
		// Execute destruction scripts
		_scriptInterpreter.executeDestruction();

		// Unload script execution
		_scriptInterpreter.unload();

		// Resume engine updates
		if (_fe3d.application_isPaused())
		{
			_fe3d.application_resume();
		}

		// Miscellaneous
		_isStarted = false;
		_isRunning = false;
		_wasCursorVisible = false;
		_wasMillisecondTimerStarted = false;
		_wasMusicPaused = false;
		_mustSkipUpdate = false;
		_pausedSoundIDs.clear();
	}
}

void ScriptExecutor::setCurrentProjectID(const string& projectID)
{
	_scriptInterpreter.setCurrentProjectID(projectID);
}

bool ScriptExecutor::isScriptEmpty()
{
	return (_script.getScriptFileCount() == 0);
}

bool ScriptExecutor::isStarted()
{
	return _isStarted;
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
		_isStarted = false;
		_isRunning = false;
	}
	else if (_scriptInterpreter.gameMustStop()) // Script must stop
	{
		this->unload();
	}
}