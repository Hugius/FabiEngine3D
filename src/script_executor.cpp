#include "script_executor.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void ScriptExecutor::start()
{
	if(_isStarted)
	{
		abort();
	}

	Tools::setCursorVisible(true);

	_scriptInterpreter->load();
	_scriptInterpreter->executeInitializeScripts();

	if(_scriptInterpreter->hasThrownError())
	{
		_stop(false);

		return;
	}
	if(_scriptInterpreter->mustStopApplication())
	{
		_stop(true);

		return;
	}

	_isStarted = true;
	_isRunning = true;
	_mustSkipUpdate = true;
}

void ScriptExecutor::update(bool isDebugging)
{
	if(_isStarted)
	{
		if(!Configuration::getInst().isApplicationExported())
		{
			_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), !_isRunning);
		}

		if(_isRunning)
		{
			if(!_mustSkipUpdate || isDebugging)
			{
				_scriptInterpreter->executeUpdateScripts(isDebugging);

				if(_scriptInterpreter->hasThrownError())
				{
					_stop(false);

					return;
				}
				if(_scriptInterpreter->mustStopApplication())
				{
					_stop(true);

					return;
				}
			}

			_mustSkipUpdate = false;
		}
	}
}

void ScriptExecutor::pause()
{
	if(!_isStarted || !_isRunning)
	{
		abort();
	}

	_wasCursorVisible = Tools::isCursorVisible();
	_wasVsyncEnabled = _fe3d->misc_isVsyncEnabled();
	_wasFirstPersonEnabled = _fe3d->camera_isFirstPersonEnabled();
	_wasThirdPersonEnabled = _fe3d->camera_isThirdPersonEnabled();

	for(const auto & soundId : _fe3d->sound3d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound3d_isStarted(soundId, index) && _fe3d->sound3d_isPaused(soundId, index))
			{
				_pausedSound3dIds.push_back({soundId, index});
			}
		}
	}

	for(const auto & soundId : _fe3d->sound2d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound2d_isStarted(soundId, index) && _fe3d->sound2d_isPaused(soundId, index))
			{
				_pausedSound2dIds.push_back({soundId, index});
			}
		}
	}

	for(const auto & clockId : _fe3d->clock_getIds())
	{
		if(_fe3d->clock_isStarted(clockId) && _fe3d->clock_isPaused(clockId))
		{
			_pausedClockIds.push_back(clockId);
		}
	}

	Tools::setCursorVisible(false);
	_fe3d->misc_setVsyncEnabled(true);
	_fe3d->camera_setFirstPersonEnabled(false);
	_fe3d->camera_setThirdPersonEnabled(false);

	for(const auto & soundId : _fe3d->sound3d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound3d_isStarted(soundId, index) && !_fe3d->sound3d_isPaused(soundId, index))
			{
				_fe3d->sound3d_pause(soundId, index);
			}
		}
	}

	for(const auto & soundId : _fe3d->sound2d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound2d_isStarted(soundId, index) && !_fe3d->sound2d_isPaused(soundId, index))
			{
				_fe3d->sound2d_pause(soundId, index);
			}
		}
	}

	for(const auto & clockId : _fe3d->clock_getIds())
	{
		if(_fe3d->clock_isStarted(clockId) && !_fe3d->clock_isPaused(clockId))
		{
			_fe3d->clock_pause(clockId);
		}
	}

	_isRunning = false;
}

void ScriptExecutor::resume()
{
	if(!_isStarted || _isRunning)
	{
		abort();
	}

	Tools::setCursorVisible(_wasCursorVisible);
	_fe3d->misc_setVsyncEnabled(_wasVsyncEnabled);
	_fe3d->camera_setFirstPersonEnabled(_wasFirstPersonEnabled);
	_fe3d->camera_setThirdPersonEnabled(_wasThirdPersonEnabled);

	for(const auto & soundId : _fe3d->sound3d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound3d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound3d_isStarted(soundId, index) && _fe3d->sound3d_isPaused(soundId, index))
			{
				_fe3d->sound3d_resume(soundId, index);
			}
		}
	}

	for(const auto & soundId : _fe3d->sound2d_getIds())
	{
		for(unsigned int index = 0; index < _fe3d->sound2d_getStartedCount(soundId); index++)
		{
			if(_fe3d->sound2d_isStarted(soundId, index) && _fe3d->sound2d_isPaused(soundId, index))
			{
				_fe3d->sound2d_resume(soundId, index);
			}
		}
	}

	for(const auto & clockId : _fe3d->clock_getIds())
	{
		if(_fe3d->clock_isStarted(clockId) && _fe3d->clock_isPaused(clockId))
		{
			_fe3d->clock_resume(clockId);
		}
	}

	for(const auto & [soundId, index] : _pausedSound3dIds)
	{
		_fe3d->sound3d_pause(soundId, index);
	}

	for(const auto & [soundId, index] : _pausedSound2dIds)
	{
		_fe3d->sound2d_pause(soundId, index);
	}

	for(const auto & clockId : _pausedClockIds)
	{
		_fe3d->clock_pause(clockId);
	}

	_isRunning = true;
	_mustSkipUpdate = true;
}

void ScriptExecutor::stop()
{
	if(!_isStarted)
	{
		abort();
	}

	_stop(true);
}

void ScriptExecutor::inject(shared_ptr<EngineInterface> fe3d)
{
	_fe3d = fe3d;
}

void ScriptExecutor::inject(shared_ptr<ScriptInterpreter> scriptInterpreter)
{
	_scriptInterpreter = scriptInterpreter;
}

void ScriptExecutor::setCurrentProjectId(const string & projectId)
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

void ScriptExecutor::_stop(bool mustExecuteTerminationScripts)
{
	if(mustExecuteTerminationScripts)
	{
		_scriptInterpreter->executeTerminateScripts();
	}

	_scriptInterpreter->unload();

	Tools::setCursorVisible(false);

	_pausedSound3dIds.clear();
	_pausedSound2dIds.clear();
	_pausedClockIds.clear();
	_isStarted = false;
	_isRunning = false;
	_wasCursorVisible = false;
	_wasVsyncEnabled = false;
	_wasFirstPersonEnabled = false;
	_wasThirdPersonEnabled = false;
	_mustSkipUpdate = false;
}