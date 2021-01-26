#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if (functionName == "fe3d:model_start_animation") // Start gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER }; // GameEntityID + animationID + loops

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_is_animation_started") // Check if gameEntity animation is started
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_is_animation_playing") // Check if gameEntity animation is playing
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_is_animation_paused") // Check if gameEntity animation is paused
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_pause_animation") // Pause gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_resume_animation") // Resume gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_fade_animation") // Fade gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER }; // GameEntityID + animationID + framestep

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_stop_animation") // Stop gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_set_animation_speed") // Set gameEntity animation speed multiplier
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL }; // GameEntityID + animationID + speed

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.setAnimationSpeedMultiplier(arguments[1].getString(), arguments[0].getString(), arguments[2].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_get_animation_frame_index") // Retrieve current animation frame
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.getAnimationFrameIndex(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
		}
	}
	else
	{
		return false;
	}

	return true;
}