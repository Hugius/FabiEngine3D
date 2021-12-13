#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimationSetter3D(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation3d_start")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_meshAnimationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_pause")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_meshAnimationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_resume")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_meshAnimationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_fade")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_meshAnimationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_stop")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_meshAnimationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation3d_set_speed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _meshAnimationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					animationData->setSpeedMultiplier(arguments[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:animation3d_set_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation autopaused option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _meshAnimationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

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

	// Cannot execute mesh animation functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation3d` functionality as networking server!");
	}

	// Return
	return true;
}