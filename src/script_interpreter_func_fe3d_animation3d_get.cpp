#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:animation3d_is_model_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				const auto result = _animation3dEditor->isModelAnimationStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_playing")
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

				const auto result = _animation3dEditor->isModelAnimationPlaying(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_autopaused")
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

				const auto result = _animation3dEditor->isModelAnimationAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_paused")
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

				const auto result = _animation3dEditor->isModelAnimationPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_speed")
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

				const auto result = _animation3dEditor->getModelAnimationSpeed(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_play_count")
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

				const auto result = _animation3dEditor->getModelAnimationPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_frame_index")
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

				const auto result = _animation3dEditor->getModelAnimationFrameIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, static_cast<int>(result)));
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