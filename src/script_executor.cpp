#include "script_executor.hpp"
#include "configuration.hpp"

ScriptExecutor::ScriptExecutor(FabiEngine3D& fe3d, Script& script, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor, Animation3dEditor& animation3dEditor, AudioEditor& audioEditor, WorldEditor& worldEditor)
	:
	_fe3d(fe3d),
	_script(script),
	_scriptInterpreter(fe3d, script, skyEditor, terrainEditor, waterEditor, modelEditor, billboardEditor, animation3dEditor, audioEditor, worldEditor)
{

}

void ScriptExecutor::load()
{
	// Start script execution & run initialization scripts
	_scriptInterpreter.load();
	_scriptInterpreter.executeInitializeScripts();
	_isStarted = true;
	_isRunning = true;
	_mustSkipUpdate = true;

	// Check for errors
	_validateExecution();
}

void ScriptExecutor::update(bool debug)
{
	if(_isStarted && _isRunning)
	{
		// Skip first frame, then update fulltime
		if(!_mustSkipUpdate || debug)
		{
			_scriptInterpreter.executeUpdateScripts(debug);
		}
		else
		{
			_mustSkipUpdate = false;
		}

		// Custom cursor is only enabled in engine preview
		if(!Config::getInst().isApplicationExported())
		{
			// Custom cursor must be inside of viewport or PC cursor must be visible
			if(_fe3d.misc_isCursorInsideViewport() || _fe3d.misc_isCursorVisible())
			{
				_fe3d.image_setVisible("@@cursor", false);
			}
		}

		// Check for errors
		_validateExecution();
	}
}

void ScriptExecutor::pause()
{
	if(_isStarted && _isRunning)
	{
		// Save cursor state
		_wasCursorVisible = _fe3d.misc_isCursorVisible();
		_fe3d.misc_setCursorVisible(false);

		// Save timer state
		_wasTimerStarted = _fe3d.misc_isMillisecondTimerStarted();
		if(_wasTimerStarted)
		{
			_fe3d.misc_stopMillisecondTimer();
		}

		// Save Vsync state
		_wasVsyncEnabled = _fe3d.misc_isVsyncEnabled();
		if(_wasVsyncEnabled)
		{
			_fe3d.misc_disableVsync();
		}

		// Save 2D sound states
		for(const auto& soundID : _fe3d.sound2d_getAllIDs())
		{
			if(_fe3d.sound2d_isPaused(soundID))
			{
				_pausedSoundIDs.push_back(soundID);
			}
		}

		// Save 3D sound states
		for (const auto& soundID : _fe3d.sound3d_getAllIDs())
		{
			if (_fe3d.sound3d_isPaused(soundID))
			{
				_pausedSoundIDs.push_back(soundID);
			}
		}

		// Pause 2D sounds
		_fe3d.sound2d_pauseAll();

		// Pause 3D sounds
		_fe3d.sound3d_pauseAll();

		// Pause engine updates & script execution
		_fe3d.application_pause();
		_isRunning = false;
	}
}

void ScriptExecutor::resume()
{
	if(_isStarted && !_isRunning)
	{
		// Reset cursor
		_fe3d.misc_centerCursor();
		_fe3d.misc_setCursorVisible(_wasCursorVisible);

		// Reset Vsync
		if(_wasVsyncEnabled)
		{
			_fe3d.misc_enableVsync();
		}

		// Reset timer
		if(_wasTimerStarted)
		{
			_fe3d.misc_startMillisecondTimer();
		}

		// Reset 2D sounds
		_fe3d.sound2d_resumeAll();
		for(const auto& soundID : _pausedSoundIDs)
		{
			_fe3d.sound2d_pause(soundID);
		}

		// Reset 3D sounds
		_fe3d.sound3d_resumeAll();
		for (const auto& soundID : _pausedSoundIDs)
		{
			_fe3d.sound3d_pause(soundID);
		}

		// Resume game logic
		_fe3d.application_resume();
		_isRunning = true;
		_mustSkipUpdate = true;
	}
}

void ScriptExecutor::unload()
{
	if(_isStarted)
	{
		// Execute terminate scripts
		_scriptInterpreter.executeTerminateScripts();

		// Unload script execution
		_scriptInterpreter.unload();

		// Resume engine updates
		if(_fe3d.application_isPaused())
		{
			_fe3d.application_resume();
		}

		// Miscellaneous
		_isStarted = false;
		_isRunning = false;
		_wasCursorVisible = false;
		_wasVsyncEnabled = false;
		_wasTimerStarted = false;
		_mustSkipUpdate = false;
		_pausedSoundIDs.clear();
	}
}

void ScriptExecutor::setCurrentProjectID(const string& projectID)
{
	_scriptInterpreter.setCurrentProjectID(projectID);
}

const bool ScriptExecutor::isScriptEmpty() const
{
	return (_script.getScriptFileCount() == 0);
}

const bool ScriptExecutor::isStarted() const
{
	return _isStarted;
}

const bool ScriptExecutor::isRunning() const
{
	return _isRunning;
}

void ScriptExecutor::_validateExecution()
{
	if(_scriptInterpreter.hasThrownError()) // Script threw an error
	{
		_scriptInterpreter.unload();
		_isStarted = false;
		_isRunning = false;
		_wasCursorVisible = false;
		_wasVsyncEnabled = false;
		_wasTimerStarted = false;
		_mustSkipUpdate = false;
		_pausedSoundIDs.clear();
	}
	else if(_scriptInterpreter.gameMustStop()) // Script must stop
	{
		this->unload();
	}
}