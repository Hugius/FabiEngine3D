#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_is_model_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->isModelAnimationStarted(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->isModelAnimationPlaying(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->isModelAnimationAutopaused(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->isModelAnimationPaused(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_speed")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->getModelAnimationSpeed(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->getModelAnimationPlayCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_frame_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				auto result = _animation3dEditor->getModelAnimationFrameIndex(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation3d` functionality as networking server!");
	}

	return true;
}