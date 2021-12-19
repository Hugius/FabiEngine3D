#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_start_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animation3dEditor.startModelAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_pause_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animation3dEditor.pauseModelAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_resume_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animation3dEditor.resumeModelAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_fade_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animation3dEditor.fadeModelAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_stop_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animation3dEditor.stopModelAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_set_model_speed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[0].getString(), arguments[1].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					animationData->setSpeedMultiplier(arguments[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_set_model_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation autopaused option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[0].getString(), arguments[1].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					animationData->setAutoPaused(arguments[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation3d` functionality as networking server!");
	}

	// Return
	return true;
}