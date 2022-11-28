#include "script_executor.hpp"
#include "tools.hpp"

void ScriptExecutor::start()
{
	if(_isStarted)
	{
		abort();
	}

	_scriptInterpreter->load();
	_scriptInterpreter->executeInitializeScripts();

	if(_scriptInterpreter->hasThrownError() || _scriptInterpreter->mustStopApplication())
	{
		_stop();

		return;
	}

	_isStarted = true;
	_mustSkipUpdate = true;
	_wasCursorVisible = Tools::isCursorVisible();
	_wasCursorInsideDisplay = Tools::isCursorInsideDisplay();
}

void ScriptExecutor::update(bool isDebugging)
{
	if(_isStarted)
	{
		if(!_mustSkipUpdate || isDebugging)
		{
			_scriptInterpreter->executeUpdateScripts(isDebugging);

			if(_scriptInterpreter->hasThrownError() || _scriptInterpreter->mustStopApplication())
			{
				_stop();

				return;
			}
		}

		if(_mustSkipUpdate)
		{
			_mustSkipUpdate = false;
		}

		if(!Tools::isApplicationExported())
		{
			if(Tools::isCursorInsideDisplay())
			{
				if(!_wasCursorInsideDisplay)
				{
					Tools::setCursorVisible(_wasCursorVisible);
				}

				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
			}
			else
			{
				if(_wasCursorInsideDisplay)
				{
					_wasCursorVisible = Tools::isCursorVisible();
				}

				Tools::setCursorVisible(false);

				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), true);
			}

			_wasCursorInsideDisplay = Tools::isCursorInsideDisplay();
		}
	}
}

void ScriptExecutor::stop()
{
	if(!_isStarted)
	{
		abort();
	}

	_stop();
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

void ScriptExecutor::_stop()
{
	if(!_scriptInterpreter->hasThrownError())
	{
		_scriptInterpreter->executeTerminateScripts();
	}

	_scriptInterpreter->unload();

	Tools::setCursorVisible(false);

	_isStarted = false;
	_mustSkipUpdate = false;
	_wasCursorVisible = false;
	_wasCursorInsideDisplay = false;
}