#include "script_executor.hpp"
#include "configuration.hpp"

void ScriptExecutor::load()
{
	_scriptInterpreter->load();
	_scriptInterpreter->executeInitializeScripts();
	_isStarted = true;
	_isRunning = true;
	_mustSkipUpdate = true;

	_validateExecution();
}

void ScriptExecutor::update(bool isDebugging)
{
	if(_isStarted && _isRunning)
	{
		if(!_mustSkipUpdate || isDebugging)
		{
			_scriptInterpreter->executeUpdateScripts(isDebugging);
		}
		else
		{
			_mustSkipUpdate = false;
		}

		if(!Config::getInst().isApplicationExported())
		{
			if(_fe3d->misc_isCursorInsideViewport() || _fe3d->misc_isCursorVisible())
			{
				_fe3d->quad2d_setVisible("@@cursor", false);
			}
		}

		_validateExecution();
	}
}

void ScriptExecutor::pause()
{
	if(_isStarted && _isRunning)
	{
		_wasCursorVisible = _fe3d->misc_isCursorVisible();
		_fe3d->misc_setCursorVisible(false);

		_wasTimerStarted = _fe3d->misc_isMillisecondTimerStarted();
		if(_wasTimerStarted)
		{
			_fe3d->misc_stopMillisecondTimer();
		}

		_wasVsyncEnabled = _fe3d->misc_isVsyncEnabled();
		if(_wasVsyncEnabled)
		{
			_fe3d->misc_disableVsync();
		}

		for(const auto& soundID : _fe3d->sound2d_getIds())
		{
			if(_fe3d->sound2d_isPaused(soundID))
			{
				_pausedSoundIDs.push_back(soundID);
			}
		}

		for(const auto& soundID : _fe3d->sound3d_getIds())
		{
			if(_fe3d->sound3d_isPaused(soundID))
			{
				_pausedSoundIDs.push_back(soundID);
			}
		}

		_fe3d->sound2d_pauseAll();

		_fe3d->sound3d_pauseAll();

		_isRunning = false;
	}
}

void ScriptExecutor::resume()
{
	if(_isStarted && !_isRunning)
	{
		_fe3d->misc_centerCursor();
		_fe3d->misc_setCursorVisible(_wasCursorVisible);

		if(_wasVsyncEnabled)
		{
			_fe3d->misc_enableVsync();
		}

		if(_wasTimerStarted)
		{
			_fe3d->misc_startMillisecondTimer();
		}

		_fe3d->sound2d_resumeAll();
		for(const auto& soundID : _pausedSoundIDs)
		{
			_fe3d->sound2d_pause(soundID);
		}

		_fe3d->sound3d_resumeAll();
		for(const auto& soundID : _pausedSoundIDs)
		{
			_fe3d->sound3d_pause(soundID);
		}

		_isRunning = true;
		_mustSkipUpdate = true;
	}
}

void ScriptExecutor::unload()
{
	if(_isStarted)
	{
		_scriptInterpreter->executeTerminateScripts();

		_scriptInterpreter->unload();

		_isStarted = false;
		_isRunning = false;
		_wasCursorVisible = false;
		_wasVsyncEnabled = false;
		_wasTimerStarted = false;
		_mustSkipUpdate = false;
		_pausedSoundIDs.clear();
	}
}

void ScriptExecutor::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void ScriptExecutor::inject(shared_ptr<ScriptInterpreter> scriptInterpreter)
{
	_scriptInterpreter = scriptInterpreter;
}

void ScriptExecutor::setCurrentProjectID(const string& projectID)
{
	_scriptInterpreter->setCurrentProjectID(projectID);
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
	if(_scriptInterpreter->hasThrownError())
	{
		_scriptInterpreter->unload();
		_isStarted = false;
		_isRunning = false;
		_wasCursorVisible = false;
		_wasVsyncEnabled = false;
		_wasTimerStarted = false;
		_mustSkipUpdate = false;
		_pausedSoundIDs.clear();
	}
	else if(_scriptInterpreter->gameMustStop())
	{
		this->unload();
	}
}