#include "script_interpreter.hpp"
#include "logger.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dMiscGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:cursor_is_visible")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			const auto result = _fe3d->misc_isCursorVisible();

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:cursor_get_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			const auto result = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPositionRelativeToViewport())).x;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if(functionName == "fe3d:cursor_get_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			const auto result = Math::convertToNdc(Tools::convertFromScreenCoords(_fe3d->misc_getCursorPositionRelativeToViewport())).y;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if(functionName == "fe3d:window_get_width")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as networking server!");
				return true;
			}

			const auto result = Config::getInst().getWindowSize().x;

			returnValues.push_back(ScriptValue(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:window_get_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as networking server!");
				return true;
			}

			const auto result = Config::getInst().getWindowSize().y;

			returnValues.push_back(ScriptValue(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:timer_is_started")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->misc_isMillisecondTimerStarted();

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:vynsc_is_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			const auto result = _fe3d->misc_isVsyncEnabled();

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}