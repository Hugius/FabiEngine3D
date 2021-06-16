#include "script_interpreter.hpp"

#include <algorithm>

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:game_pause")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access pausing functionality as a networking server!");
				return true;
			}

			// Pause engine
			_fe3d.engine_pause();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:game_resume")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access pausing functionality as a networking server!");
				return true;
			}

			// Resume engine
			_fe3d.engine_resume();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:game_stop")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			if (_fe3d.engine_isGameExported()) // Game preview
			{
				_fe3d.engine_stop();
			}
			else // Engine preview
			{
				_gameMustStop = true;
			}
			
			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateListValueAmount(arguments, 1))
		{
			// Determine which type of value to print
			if (arguments[0].getType() == ScriptValueType::VEC3)
			{
				_fe3d.logger_throwInfo(_fe3d.misc_vec2str(arguments[0].getVec3()));
			}
			else if (arguments[0].getType() == ScriptValueType::STRING)
			{
				_fe3d.logger_throwInfo(arguments[0].getString());
			}
			else if (arguments[0].getType() == ScriptValueType::DECIMAL)
			{
				string decimalString = to_string(arguments[0].getDecimal());
				_fe3d.logger_throwInfo(decimalString.substr(0, decimalString.size() - 1));
			}
			else if (arguments[0].getType() == ScriptValueType::INTEGER)
			{
				_fe3d.logger_throwInfo(to_string(arguments[0].getInteger()));
			}
			else if (arguments[0].getType() == ScriptValueType::BOOLEAN)
			{
				_fe3d.logger_throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}
			else
			{
				_fe3d.logger_throwError("Script interpreter print received empty value!");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_center")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Center cursor
			_fe3d.misc_centerCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_show")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Show cursor
			_fe3d.misc_showCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_hide")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Hide cursor
			_fe3d.misc_hideCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_is_visible")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Return cursor visbility
			auto result = _fe3d.misc_isCursorVisible();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_x")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Get cursor position X
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_y")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access cursor functionality as a networking server!");
				return true;
			}

			// Get cursor position Y
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:window_get_width")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access window functionality as a networking server!");
				return true;
			}

			// Get window width
			auto result = _fe3d.misc_getWindowSize().x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:window_get_height")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access window functionality as a networking server!");
				return true;
			}

			// Get window height
			auto result = _fe3d.misc_getWindowSize().y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:timer_start")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:timer_stop")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:wireframe_enable_rendering")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wireframe functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access wireframe functionality as a networking server!");
				return true;
			}

			// Enable wireframe rendering
			_fe3d.misc_enableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:wireframe_disable_rendering")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wireframe functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access wireframe functionality as a networking server!");
				return true;
			}

			// Disable wireframe rendering
			_fe3d.misc_disableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_enable_rendering")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access aabbs functionality as a networking server!");
				return true;
			}

			// Enable AABB rendering
			_fe3d.misc_enableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_disable_rendering")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access aabbs functionality as a networking server!");
				return true;
			}

			// Disable AABB rendering
			_fe3d.misc_disableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:time_interval")
	{
		auto types = { ScriptValueType::INTEGER };

		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:vsync_enable")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access vsync functionality as a networking server!");
				return true;
			}

			// Enable Vsync
			_fe3d.misc_enableVsync();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:vsync_disable")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access vsync functionality as a networking server!");
				return true;
			}

			// Disable Vsync
			_fe3d.misc_disableVsync();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:vynsc_is_enabled")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access vsync functionality as a networking server!");
				return true;
			}

			// Return Vsync status
			auto result = _fe3d.misc_isVsyncEnabled();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}