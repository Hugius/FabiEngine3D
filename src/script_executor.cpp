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
	else if(_scriptInterpreter->mustStopApplication())
	{
		_stop(true);

		return;
	}

	_isStarted = true;
	_mustSkipUpdate = true;
}

void ScriptExecutor::update(bool isDebugging)
{
	if(_isStarted)
	{
		if(!_mustSkipUpdate || isDebugging)
		{
			_scriptInterpreter->executeUpdateScripts(isDebugging);

			if(_scriptInterpreter->hasThrownError())
			{
				_stop(false);

				return;
			}
			else if(_scriptInterpreter->mustStopApplication())
			{
				_stop(true);

				return;
			}
		}

		if(_mustSkipUpdate)
		{
			_mustSkipUpdate = false;
		}
	}
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

void ScriptExecutor::_stop(bool mustExecuteTerminationScripts)
{
	if(mustExecuteTerminationScripts)
	{
		_scriptInterpreter->executeTerminateScripts();
	}

	_scriptInterpreter->unload();

	Tools::setCursorVisible(false);

	_isStarted = false;
	_mustSkipUpdate = false;
}