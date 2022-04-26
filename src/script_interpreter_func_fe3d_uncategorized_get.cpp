#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dUncategorizedGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
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

			const auto result = Tools::isCursorVisible();

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

			const auto result = clamp(Tools::convertPositionRelativeToDisplay(Tools::convertToNdc(Tools::getCursorPosition())).x, -1.0f, 1.0f);

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

			const auto result = clamp(Tools::convertPositionRelativeToDisplay(Tools::convertToNdc(Tools::getCursorPosition())).y, -1.0f, 1.0f);

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

			const auto result = Configuration::getInst().getWindowSize().x;

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

			const auto result = Configuration::getInst().getWindowSize().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:time_is_passed")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto result = ((_fe3d->misc_getPassedUpdateCount() % args[0]->getInteger()) == 0);

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
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