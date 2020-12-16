#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if (functionName == "fe3d:model_animation_start") // Start gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.startAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_animation_speed_set") // Set gameEntity animation speed multiplier
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.setAnimationSpeedMultiplier(arguments[0].getString(), arguments[1].getString(), arguments[2].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_animation_isplaying") // Check if gameEntity animation is playing
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPlaying(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_animation_ispaused") // Check if gameEntity animation is paused
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPaused(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_animation_pause") // Pause gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.pauseAnimation(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_animation_resume") // Resume gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.resumeAnimation(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_animation_fade") // Fade gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.fadeAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_animation_stop") // Stop gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.stopAnimation(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}