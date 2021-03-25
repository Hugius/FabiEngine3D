#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dAudioEntity(const string& ID, bool previewEntity)
{
	// Cannot request/delete a preview entity
	if (!previewEntity && ID.front() == '@')
	{
		_throwScriptError("Requested audio ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.audioEntity_isExisting(ID))
	{
		if (previewEntity)
		{
			_throwScriptError("Requested audio with ID \"" + ID.substr(1) + "\" does not exist!");
		}
		else
		{
			_throwScriptError("Requested audio with ID \"" + ID + "\" does not exist!");
		}

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dAudioEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:audio_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested audio ID cannot start with '@'"); 
				return true;
			}

			// Check if existing
			auto result = _fe3d.audioEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:audio_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested audio ID cannot start with '@'");
				return true;
			}

			// Find full audioEntity IDs based on part ID
			for (auto& ID : _fe3d.audioEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview audio
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:audio_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.audioEntity_getAllIDs();

			// For every audio
			for (auto& ID : result)
			{
				// Only non-preview audios
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:audio_place2D")
	{
		auto types =
		{
			ScriptValueType::STRING, // New audioEntity ID
			ScriptValueType::STRING, // Preview audioEntity ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New audio ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New audio ID cannot start with '@'");
				return true;
			}

			// Check if audio entity already exists
			if (_fe3d.audioEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Audio with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview audio ID
			if (_validateFe3dAudioEntity("@" + arguments[1].getString(), true))
			{
				auto filePath = _fe3d.audioEntity_getFilePath("@" + arguments[1].getString());
				_fe3d.audioEntity_add2D(arguments[0].getString(), filePath);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_place3D")
	{
		auto types =
		{
			ScriptValueType::STRING, // New audioEntity ID
			ScriptValueType::STRING, // Preview audioEntity ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, // Max volume
			ScriptValueType::DECIMAL // Max distance
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New audio ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New audio ID cannot start with '@'");
				return true;
			}

			// Check if audio entity already exists
			if (_fe3d.audioEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Audio with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview audio ID
			if (_validateFe3dAudioEntity("@" + arguments[1].getString(), true))
			{
				auto filePath = _fe3d.audioEntity_getFilePath("@" + arguments[1].getString());
				_fe3d.audioEntity_add3D(
					arguments[0].getString(),
					filePath,
					Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()),
					arguments[5].getDecimal(),
					arguments[6].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_play")
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::INTEGER, // Loops
			ScriptValueType::DECIMAL  // Volume
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_is_playing") // Check if audioEntity is playing
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				auto result = _fe3d.audioEntity_isPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:audio_pause") // Pause audioEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_pause(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_pause_all") // Pause all audioEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_pauseAll();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_is_paused") // Check if audioEntity is paused
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				auto result = _fe3d.audioEntity_isPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:audio_resume") // Resume audioEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_resume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_resume_all") // Resume all audioEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_resumeAll();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_stop") // Stop audioEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_stop(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_stop_all") // Stop all audioEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				_fe3d.audioEntity_stopAll();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_set_volume") // Set audioEntity volume
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 2D audio
				if (_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change volume of 3D audio!");
					return true;
				}

				// Execute function
				_fe3d.audioEntity_setVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_get_volume") // Get audioEntity volume
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				auto result = _fe3d.audioEntity_getVolume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:audio_set_position") // Set audioEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change position of 2D audio!");
					return true;
				}

				// Execute function
				_fe3d.audioEntity_setPosition(
					arguments[0].getString(), 
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_get_position") // Get audioEntity position
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change position of 2D audio!");
					return true;
				}

				auto result = _fe3d.audioEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:audio_set_max_volume") // Set max audioEntity volume
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change maximum volume of 2D audio!");
					return true;
				}

				// Execute function
				_fe3d.audioEntity_setMaxVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_get_max_volume") // Get max audioEntity volume
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change maximum volume of 2D audio!");
					return true;
				}

				// Execute function
				auto result = _fe3d.audioEntity_getMaxVolume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:audio_set_max_distance") // Set max audioEntity distance
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change maximum distance of 2D audio!");
					return true;
				}

				// Execute function
				_fe3d.audioEntity_setMaxDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:audio_get_max_distance") // Get max audioEntity distance
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing audio ID
			if (_validateFe3dAudioEntity(arguments[0].getString()))
			{
				// Only for 3D audio
				if (!_fe3d.audioEntity_is3D(arguments[0].getString()))
				{
					_throwScriptError("Cannot change maximum distance of 2D audio!");
					return true;
				}

				// Execute function
				auto result = _fe3d.audioEntity_getMaxDistance(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}