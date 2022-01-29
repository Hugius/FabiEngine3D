#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dMiscSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:application_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(Config::getInst().isApplicationExported())
			{
				_fe3d->application_stop();
			}
			else
			{
				_mustStopApplication = true;
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:print")
	{
		if(_validateArgumentCount(args, 1))
		{
			if(args[0].getType() == SVT::STRING)
			{
				Logger::throwInfo(args[0].getString());
			}
			else if(args[0].getType() == SVT::DECIMAL)
			{
				string decimalString = to_string(args[0].getDecimal());
				Logger::throwInfo(decimalString.substr(0, decimalString.size() - 1));
			}
			else if(args[0].getType() == SVT::INTEGER)
			{
				Logger::throwInfo(to_string(args[0].getInteger()));
			}
			else if(args[0].getType() == SVT::BOOLEAN)
			{
				Logger::throwInfo(args[0].getBoolean() ? "true" : "false");
			}
			else
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dMiscFunction");
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_set_visible")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			_fe3d->misc_setCursorVisible(args[0].getBoolean());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_center")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			_fe3d->misc_centerCursor();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_start")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d->misc_startMillisecondTimer();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->misc_stopMillisecondTimer();

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:vsync_enable")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			_fe3d->misc_enableVsync();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:vsync_disable")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_fe3d->server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			_fe3d->misc_disableVsync();

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:time_interval")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = ((_fe3d->misc_getPassedUpdateCount() % args[0].getInteger()) == 0);

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}