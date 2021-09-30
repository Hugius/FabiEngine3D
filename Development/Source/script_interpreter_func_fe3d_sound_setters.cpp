#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dSoundSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:sound_place_2D")
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