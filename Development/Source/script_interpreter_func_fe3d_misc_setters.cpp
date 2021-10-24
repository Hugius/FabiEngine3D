#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dMiscSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:application_pause")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_pause` as a networking server!");
				return true;
			}

			// Pause engine
			_fe3d.application_pause();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:application_resume")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_resume` as a networking server!");
				return true;
			}

			// Resume engine
			_fe3d.application_resume();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:application_stop")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			if (_fe3d.application_isExported()) // Application preview
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
	else if (functionName == "fe3d:print")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 1))
		{
			// Determine which type of value to print
			if (arguments[0].getType() == SVT::VEC3)
			{
				Logger::throwInfo(Tools::vec2str(arguments[0].getVec3()));
			}
			else if (arguments[0].getType() == SVT::STRING)
			{
				Logger::throwInfo(arguments[0].getString());
			}
			else if (arguments[0].getType() == SVT::DECIMAL)
			{
				string decimalString = to_string(arguments[0].getDecimal());
				Logger::throwInfo(decimalString.substr(0, decimalString.size() - 1));
			}
			else if (arguments[0].getType() == SVT::INTEGER)
			{
				Logger::throwInfo(to_string(arguments[0].getInteger()));
			}
			else if (arguments[0].getType() == SVT::BOOLEAN)
			{
				Logger::throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}
			else
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dMiscFunction");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_set_visible")
	{
		auto types = { SVT::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Set cursor visibility
			_fe3d.misc_setCursorVisible(arguments[0].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_center")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Center cursor
			_fe3d.misc_centerCursor();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:timer_start")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:timer_stop")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:wireFrame_enable_rendering")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wire frame functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireFrame` functionality as a networking server!");
				return true;
			}

			// Enable wire frame rendering
			_fe3d.misc_enableWireFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:wireFrame_disable_rendering")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wire frame functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireFrame` functionality as a networking server!");
				return true;
			}

			// Disable wire frame rendering
			_fe3d.misc_disableWireFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_enable_rendering")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as a networking server!");
				return true;
			}

			// Enable AABB rendering
			_fe3d.misc_enableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_disable_rendering")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as a networking server!");
				return true;
			}

			// Disable AABB rendering
			_fe3d.misc_disableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:time_interval")
	{
		auto types = { SVT::INTEGER };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:vsync_enable")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
				return true;
			}

			// Enable Vsync
			_fe3d.misc_enableVsync();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:vsync_disable")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
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