#include "script_interpreter.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dMiscGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:cursor_is_visible")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Return cursor visbility
			auto result = _fe3d.misc_isCursorVisible();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_x")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Get cursor position X
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_y")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Get cursor position Y
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:window_get_width")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as a networking server!");
				return true;
			}

			// Get window width
			auto result = _fe3d.misc_getWindowSize().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:window_get_height")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as a networking server!");
				return true;
			}

			// Get window height
			auto result = _fe3d.misc_getWindowSize().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:timer_is_started")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_isMillisecondTimerStarted();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:vynsc_is_enabled")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
				return true;
			}

			// Return Vsync status
			auto result = _fe3d.misc_isVsyncEnabled();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}