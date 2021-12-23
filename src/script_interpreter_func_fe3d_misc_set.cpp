#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dMiscSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:application_pause")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_pause` functionality as a networking server!");
				return true;
			}

			// Pause engine
			_fe3d.application_pause();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:application_resume")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_resume` functionality as a networking server!");
				return true;
			}

			// Resume engine
			_fe3d.application_resume();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:application_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(Config::getInst().isApplicationExported()) // Application preview
			{
				_fe3d.application_stop();
			}
			else // Engine preview
			{
				_mustStopApplication = true;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:print")
	{
		if(_validateArgumentCount(args, 1))
		{
			// Determine which type of value to print
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

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_set_visible")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			// Set cursor visibility
			_fe3d.misc_setCursorVisible(args[0].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_center")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			// Center cursor
			_fe3d.misc_centerCursor();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_start")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_stop")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:wireframe_enable_rendering")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireframe` functionality as networking server!");
				return true;
			}

			// Enable wireframe rendering
			_fe3d.misc_enableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:wireframe_disable_rendering")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireframe` functionality as networking server!");
				return true;
			}

			// Disable wireframe rendering
			_fe3d.misc_disableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabbs_enable_rendering")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as networking server!");
				return true;
			}

			// Enable AABB rendering
			_fe3d.misc_enableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabbs_disable_rendering")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as networking server!");
				return true;
			}

			// Disable AABB rendering
			_fe3d.misc_disableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:time_interval")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = _fe3d.misc_checkInterval(args[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:vsync_enable")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			// Enable Vsync
			_fe3d.misc_enableVsync();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:vsync_disable")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			// Disable Vsync
			_fe3d.misc_disableVsync();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}