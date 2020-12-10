#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dGameEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:model_animation_start") // Start gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.startAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}

		return true;
	}
	else if (functionName == "fe3d:model_animation_isplaying") // Check if gameEntity animation is playing
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.isAnimationPlaying(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN));
		}

		return true;
	}
	else if (functionName == "fe3d:model_animation_stop") // Stop gameEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_animationEditor.stopAnimation(arguments[0].getString(), arguments[1].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}

		return true;
	}
	else if (functionName == "fe3d:model_position_set") // Set gameEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::VEC3 };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setPosition(arguments[0].getString(), arguments[1].getVec3());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}

		return true;
	}
	else if (functionName == "fe3d:model_position_get") // Get gameEntity position
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}

		return true;
	}
	else if (functionName == "fe3d:model_place") // Create gameEntity
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING,
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL,
		};

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}

		return true;
	}
	else if (functionName == "fe3d:model_delete") // Delete gameEntity
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}