#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimationGetter3D(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_is_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_fading")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animation3dEditor.isAnimationFading(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_speed")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->getSpeedMultiplier();
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_is_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation autopause option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->isAutoPaused();
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_get_frame_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation frame index with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animation3dEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

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