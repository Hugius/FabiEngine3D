#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_start_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->startModelAnimation(args[0].getString(), args[1].getString(), args[2].getInteger());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_autopause_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->autopauseModelAnimation(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_pause_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->pauseModelAnimation(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_resume_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->resumeModelAnimation(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_stop_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->stopModelAnimation(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_set_model_speed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0].getString()) && _validateFe3dModel(args[1].getString(), false))
			{
				_animation3dEditor->setModelAnimationSpeed(args[0].getString(), args[1].getString(), args[2].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
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