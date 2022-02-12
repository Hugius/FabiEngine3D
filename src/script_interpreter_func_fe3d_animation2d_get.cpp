#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:quad3d_is_animation_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad3d_isAnimationPlaying(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad3d_isAnimationPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad3d_isAnimationAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad3d_getAnimationRowIndex(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad3d_getAnimationColumnIndex(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad3d_getAnimationPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation_interval_divider")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad3d_getAnimationIntervalDivider(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad2d_isAnimationPlaying(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad2d_isAnimationPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad2d_isAnimationAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad2d_getAnimationRowIndex(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad2d_getAnimationColumnIndex(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = _fe3d->quad2d_getAnimationPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation_interval_divider")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				const auto result = static_cast<int>(_fe3d->quad2d_getAnimationIntervalDivider(args[0]->getString(), args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:animation2d` functionality as a networking server");
		return true;
	}

	return true;
}