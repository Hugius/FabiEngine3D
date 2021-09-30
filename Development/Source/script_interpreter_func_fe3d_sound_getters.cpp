#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dSoundGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:sound_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview sound
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested sound with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.sound_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:sound_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview sound
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested sound with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full sound IDs based on part ID
			for (const auto& ID : _fe3d.sound_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview sound
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:sound_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.sound_getAllIDs();

			// For every sound
			for (const auto& ID : result)
			{
				// Only non-preview sounds
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:sound_is_started")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				auto result = _fe3d.sound_isStarted(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_is_playing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				auto result = _fe3d.sound_isPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_is_paused")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				auto result = _fe3d.sound_isPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_get_volume")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				auto result = _fe3d.sound_getVolume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_get_position")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot retrieve position of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				auto result = _fe3d.sound_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_get_max_volume")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot retrieve maximum volume of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				auto result = _fe3d.sound_getMaxVolume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sound_get_max_distance")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot retrieve maximum distance of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				auto result = _fe3d.sound_getMaxDistance(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sound functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sound` functionality as a networking server!");
	}

	return true;
}