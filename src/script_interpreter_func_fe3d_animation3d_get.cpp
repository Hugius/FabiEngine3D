#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation3dGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_is_model_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isModelAnimationStarted(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isModelAnimationPlaying(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isModelAnimationPaused(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_fading")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isModelAnimationFading(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_speed")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[0].getString(), arguments[1].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->getSpeedMultiplier();
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_model_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation autopause option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[0].getString(), arguments[1].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->isAutoPaused();
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_model_frame_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation frame index with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[0].getString(), arguments[1].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->getFrameIndex();
					returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
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