#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dSound(const string& ID, bool isPreviewEntity)
{
	if (isPreviewEntity)
	{
		// Validate existence
		if (!_fe3d.sound_isExisting(ID))
		{
			_throwScriptError("requested preview sound with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// Cannot access a preview sound
		if (!isPreviewEntity && ID.front() == '@')
		{
			_throwScriptError("ID of requested sound with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if (!_fe3d.sound_isExisting(ID))
		{
			_throwScriptError("requested sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dSoundFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
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
	else if (functionName == "fe3d:sound_place_2D")
	{
		auto types =
		{
			ScriptValueType::STRING, // New sound ID
			ScriptValueType::STRING, // Preview sound ID
			ScriptValueType::DECIMAL // Volume
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// New sound ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("new sound ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if sound already exists
			if (_fe3d.sound_isExisting(arguments[0].getString()))
			{
				_throwScriptError("sound with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview sound ID
			if (_validateFe3dSound("@" + arguments[1].getString(), true))
			{
				auto filePath = _fe3d.sound_getFilePath("@" + arguments[1].getString());
				_fe3d.sound_create(arguments[0].getString(), filePath);
				_fe3d.sound_setVolume(arguments[0].getString(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_place_3D")
	{
		auto types =
		{
			ScriptValueType::STRING, // New sound ID
			ScriptValueType::STRING, // Preview sound ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, // Max volume
			ScriptValueType::DECIMAL // Max distance
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string newID = arguments[0].getString();
			string previewID = arguments[1].getString();

			// New sound ID cannot start with '@'
			if (newID.front() == '@')
			{
				_throwScriptError("new sound ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if sound already exists
			if (_fe3d.sound_isExisting(newID))
			{
				_throwScriptError("sound with ID \"" + newID + "\" already exists!");
				return true;
			}

			// Validate preview sound ID
			if (_validateFe3dSound("@" + previewID, true))
			{
				// Temporary values
				auto position = Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal());
				auto maxVolume = arguments[5].getDecimal();
				auto maxDistance = arguments[6].getDecimal();

				// Add sound
				_sceneEditor.copyPreviewSound(newID, ("@" + previewID), position);
				_fe3d.sound_setMaxVolume(newID, maxVolume);
				_fe3d.sound_setMaxDistance(newID, maxDistance);

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_enable")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_enableSounds();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:sound_disable")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_disableSounds();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:sound_play")
	{
		auto types =
		{
			ScriptValueType::STRING,  // ID
			ScriptValueType::INTEGER, // Loops
			ScriptValueType::INTEGER  // FadeMS
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_play_forced")
	{
		auto types =
		{
			ScriptValueType::STRING,  // ID
			ScriptValueType::INTEGER, // Loops
			ScriptValueType::INTEGER  // FadeMS
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), true);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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
	else if (functionName == "fe3d:sound_pause")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_pause(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_pause_all")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.sound_pauseAll();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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
	else if (functionName == "fe3d:sound_resume")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_resume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_resume_all")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.sound_resumeAll();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:sound_stop")
	{
		auto types =
		{
			ScriptValueType::STRING,  // ID
			ScriptValueType::INTEGER  // FadeMS
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				_fe3d.sound_stop(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sound_stop_all")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.sound_stopAll();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:sound_set_volume")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 2D sound
				if (_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot change volume of 3D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				_fe3d.sound_setVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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
	else if (functionName == "fe3d:sound_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot change position of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				_fe3d.sound_setPosition(
					arguments[0].getString(), 
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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
	else if (functionName == "fe3d:sound_set_max_volume")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot change maximum volume of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				_fe3d.sound_setMaxVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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
	else if (functionName == "fe3d:sound_set_max_distance")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing sound ID
			if (_validateFe3dSound(arguments[0].getString()))
			{
				// Only for 3D sound
				if (!_fe3d.sound_is3D(arguments[0].getString()))
				{
					_throwScriptError("cannot change maximum distance of 2D sound with ID \"" + arguments[0].getString() + "\"!");
					return true;
				}

				// Execute function
				_fe3d.sound_setMaxDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
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