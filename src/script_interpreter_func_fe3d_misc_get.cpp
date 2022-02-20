#include "script_interpreter.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dMiscGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:cursor_is_visible")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:cursor` functionality as a networking server");
				return true;
			}

			const auto result = _fe3d->misc_isCursorVisible();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:cursor_get_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:cursor` functionality as a networking server");
				return true;
			}

			const auto result = clamp(Tools::convertPositionRelativeToDisplay(Tools::convertToNdc(_fe3d->misc_getCursorPosition())).x, -1.0f, 1.0f);

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:cursor_get_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:cursor` functionality as a networking server");
				return true;
			}

			const auto result = clamp(Tools::convertPositionRelativeToDisplay(Tools::convertToNdc(_fe3d->misc_getCursorPosition())).y, -1.0f, 1.0f);

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:window_get_width")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:window` functionality as a networking server");
				return true;
			}

			const auto result = Config::getInst().getWindowSize().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:window_get_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:window` functionality as a networking server");
				return true;
			}

			const auto result = Config::getInst().getWindowSize().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:clock_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}

			const auto result = _fe3d->clock_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_is_started")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}
			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock is not existing");
				return true;
			}

			const auto result = _fe3d->clock_isStarted(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_is_ticking")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}
			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock is not existing");
				return true;
			}
			if(!_fe3d->clock_isStarted(args[0]->getString()))
			{
				_throwRuntimeError("clock is not started");
				return true;
			}

			const auto result = _fe3d->clock_isTicking(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_is_paused")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}
			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock is not existing");
				return true;
			}
			if(!_fe3d->clock_isStarted(args[0]->getString()))
			{
				_throwRuntimeError("clock is not started");
				return true;
			}

			const auto result = _fe3d->clock_isPaused(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_get_delta")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}
			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock is not existing");
				return true;
			}
			if(_fe3d->clock_isStarted(args[0]->getString()))
			{
				_throwRuntimeError("clock is still started");
				return true;
			}

			const auto result = _fe3d->clock_getDeltaTime(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:vsync_is_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwRuntimeError("cannot access `fe3d:vsync` functionality as a networking server");
				return true;
			}

			const auto result = _fe3d->misc_isVsyncEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}