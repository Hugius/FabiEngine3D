#include "script_executor.hpp"
#include "configuration.hpp"

void ScriptExecutor::start()
{
	_fe3d->misc_centerCursor();

	_scriptInterpreter->load();
	_scriptInterpreter->executeInitializeScripts();
	_isStarted = true;
	_isRunning = true;
	_mustSkipUpdate = true;
	_wasCursorVisible = _fe3d->misc_isCursorVisible();

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

		if(!Configuration::getInst().isApplicationExported())
		{
			const auto isCursorInsideDisplay = _fe3d->misc_isCursorInsideDisplay();

			_fe3d->quad2d_setVisible("@@cursor", !isCursorInsideDisplay);

			if(_wasCursorInsideDisplay && !isCursorInsideDisplay)
			{
				_wasCursorVisible = _fe3d->misc_isCursorVisible();

				_fe3d->misc_setCursorVisible(false);
			}
			if(!_wasCursorInsideDisplay && isCursorInsideDisplay)
			{
				_fe3d->misc_setCursorVisible(_wasCursorVisible);
			}

			_wasCursorInsideDisplay = isCursorInsideDisplay;
		}

		_validateExecution();
	}
}

void ScriptExecutor::pause()
{
	if(_isStarted && _isRunning)
	{
		_wasVsyncEnabled = _fe3d->misc_isVsyncEnabled();
		_wasFirstPersonEnabled = _fe3d->camera_isFirstPersonEnabled();
		_wasThirdPersonEnabled = _fe3d->camera_isThirdPersonEnabled();

		for(const auto& soundId : _fe3d->sound3d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound3d_isStarted(soundId, index) && _fe3d->sound3d_isPaused(soundId, index))
				{
					_pausedSound3dIds.push_back({soundId, index});
				}
			}
		}

		for(const auto& soundId : _fe3d->sound2d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound2d_isStarted(soundId, index) && _fe3d->sound2d_isPaused(soundId, index))
				{
					_pausedSound2dIds.push_back({soundId, index});
				}
			}
		}

		for(const auto& clockId : _fe3d->clock_getIds())
		{
			if(_fe3d->clock_isStarted(clockId) && _fe3d->clock_isPaused(clockId))
			{
				_pausedClockIds.push_back(clockId);
			}
		}

		_fe3d->misc_setVsyncEnabled(true);
		_fe3d->misc_setCursorVisible(false);
		_fe3d->camera_setFirstPersonEnabled(false);
		_fe3d->camera_setThirdPersonEnabled(false);

		for(const auto& soundId : _fe3d->sound3d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound3d_isStarted(soundId, index) && !_fe3d->sound3d_isPaused(soundId, index))
				{
					_fe3d->sound3d_pause(soundId, index);
				}
			}
		}

		for(const auto& soundId : _fe3d->sound2d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound2d_isStarted(soundId, index) && !_fe3d->sound2d_isPaused(soundId, index))
				{
					_fe3d->sound2d_pause(soundId, index);
				}
			}
		}

		for(const auto& clockId : _fe3d->clock_getIds())
		{
			if(_fe3d->clock_isStarted(clockId) && !_fe3d->clock_isPaused(clockId))
			{
				_fe3d->clock_pause(clockId);
			}
		}

		_isRunning = false;
	}
}

void ScriptExecutor::resume()
{
	if(_isStarted && !_isRunning)
	{
		_fe3d->misc_centerCursor();
		_fe3d->misc_setVsyncEnabled(_wasVsyncEnabled);
		_fe3d->misc_setCursorVisible(_wasCursorVisible);
		_fe3d->camera_setFirstPersonEnabled(_wasFirstPersonEnabled);
		_fe3d->camera_setThirdPersonEnabled(_wasThirdPersonEnabled);

		for(const auto& soundId : _fe3d->sound3d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound3d_isStarted(soundId, index) && _fe3d->sound3d_isPaused(soundId, index))
				{
					_fe3d->sound3d_resume(soundId, index);
				}
			}
		}

		for(const auto& soundId : _fe3d->sound2d_getIds())
		{
			for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
			{
				if(_fe3d->sound2d_isStarted(soundId, index) && _fe3d->sound2d_isPaused(soundId, index))
				{
					_fe3d->sound2d_resume(soundId, index);
				}
			}
		}

		for(const auto& clockId : _fe3d->clock_getIds())
		{
			if(_fe3d->clock_isStarted(clockId) && _fe3d->clock_isPaused(clockId))
			{
				_fe3d->clock_resume(clockId);
			}
		}

		for(const auto& [soundId, index] : _pausedSound3dIds)
		{
			_fe3d->sound3d_pause(soundId, index);
		}

		for(const auto& [soundId, index] : _pausedSound2dIds)
		{
			_fe3d->sound2d_pause(soundId, index);
		}

		for(const auto& clockId : _pausedClockIds)
		{
			_fe3d->clock_pause(clockId);
		}

		_isRunning = true;
		_mustSkipUpdate = true;
	}
}

void ScriptExecutor::stop()
{
	if(_isStarted)
	{
		_scriptInterpreter->executeTerminateScripts();

		_scriptInterpreter->unload();

		_pausedSound3dIds.clear();
		_pausedSound2dIds.clear();
		_pausedClockIds.clear();
		_isStarted = false;
		_isRunning = false;
		_wasVsyncEnabled = false;
		_wasCursorVisible = false;
		_wasCursorInsideDisplay = false;
		_wasFirstPersonEnabled = false;
		_wasThirdPersonEnabled = false;
		_mustSkipUpdate = false;
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

void ScriptExecutor::setCurrentProjectId(const string& projectId)
{
	_scriptInterpreter->setCurrentProjectId(projectId);
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

		_pausedSound3dIds.clear();
		_pausedSound2dIds.clear();
		_pausedClockIds.clear();
		_isStarted = false;
		_isRunning = false;
		_wasVsyncEnabled = false;
		_wasCursorVisible = false;
		_wasCursorInsideDisplay = false;
		_wasFirstPersonEnabled = false;
		_wasThirdPersonEnabled = false;
		_mustSkipUpdate = false;
	}
	else if(_scriptInterpreter->gameMustStop())
	{
		this->stop();
	}
}