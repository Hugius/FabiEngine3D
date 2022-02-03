#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:animation3d_model_start")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is already started");
					return true;
				}
				if((args[2]->getInteger() < -1) || (args[2]->getInteger() == 0))
				{
					_throwRuntimeError("play count is invalid");
					return true;
				}

				for(const auto& partId : _animation3dEditor->getAnimationPartIds(args[0]->getString()))
				{
					if(!partId.empty())
					{
						if(!_fe3d->model_hasPart(args[1]->getString(), partId))
						{
							_throwRuntimeError("model does not have the required animation parts");
							return true;
						}
					}
				}

				_animation3dEditor->startModelAnimation(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_pause")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(_animation3dEditor->isModelAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not playing");
					return true;
				}

				_animation3dEditor->pauseModelAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_pause_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				_animation3dEditor->pauseModelAnimations();

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_autopause")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(_animation3dEditor->isModelAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_animation3dEditor->autopauseModelAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_autopause_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				_animation3dEditor->autopauseModelAnimations();

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_resume")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(!_animation3dEditor->isModelAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not paused");
					return true;
				}

				_animation3dEditor->resumeModelAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_resume_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				_animation3dEditor->resumeModelAnimations();

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_stop")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_animation3dEditor->stopModelAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_stop_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				_animation3dEditor->stopModelAnimations();

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_model_set_speed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_animation3dEditor->setModelAnimationSpeed(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

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