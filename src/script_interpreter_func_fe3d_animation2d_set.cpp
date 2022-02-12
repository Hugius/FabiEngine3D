#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:quad3d_start_animation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is already started");
					return true;
				}
				if((args[2]->getInteger() < -1) || (args[2]->getInteger() == 0))
				{
					_throwRuntimeError("play count is invalid");
					return true;
				}

				_fe3d->quad3d_startAnimation(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_pause_animation")
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
				if(_fe3d->quad3d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_fe3d->quad3d_pauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_autopause_animation")
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
				if(_fe3d->quad3d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_fe3d->quad3d_autopauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_resume_animation")
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
				if(!_fe3d->quad3d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not paused");
					return true;
				}

				_fe3d->quad3d_resumeAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_stop_animation")
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

				_fe3d->quad3d_stopAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_set_animation_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad3d_setAnimationRowIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_set_animation_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad3d_setAnimationColumnIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_set_animation_interval_divider")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad3d_setAnimationIntervalDivider(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_start_animation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is already started");
					return true;
				}
				if((args[2]->getInteger() < -1) || (args[2]->getInteger() == 0))
				{
					_throwRuntimeError("play count is invalid");
					return true;
				}

				_fe3d->quad2d_startAnimation(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_pause_animation")
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
				if(_fe3d->quad2d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_fe3d->quad2d_pauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_autopause_animation")
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
				if(_fe3d->quad2d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_fe3d->quad2d_autopauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_resume_animation")
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
				if(!_fe3d->quad2d_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not paused");
					return true;
				}

				_fe3d->quad2d_resumeAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_stop_animation")
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

				_fe3d->quad2d_stopAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad2d_setAnimationRowIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad2d_setAnimationColumnIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation_interval_divider")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->quad2d_setAnimationIntervalDivider(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:animation3d` functionality as a networking server");
		return true;
	}

	return true;
}