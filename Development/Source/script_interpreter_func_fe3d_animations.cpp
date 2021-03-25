#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if (functionName == "fe3d:model_start_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER }; // ModelEntityID + animationID + loops

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_is_animation_started")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_is_animation_playing")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_is_animation_paused")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			auto result = _animationEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_pause_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_resume_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_fade_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER }; // ModelEntityID + animationID + framestep

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_stop_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_set_animation_speed")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL }; // ModelEntityID + animationID + speed

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.setAnimationSpeedMultiplier(arguments[1].getString(), arguments[0].getString(), arguments[2].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_get_animation_frame_index")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // ModelEntityID + animationID

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