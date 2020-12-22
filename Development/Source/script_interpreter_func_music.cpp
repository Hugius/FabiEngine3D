#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dMusicFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:music_add_to_playlist") // Add music to playlist
	{
		auto types =
		{
			ScriptValueType::STRING, // Preview audioEntity ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate preview audio ID
			if (_validateFe3dAudioEntity("@" + arguments[0].getString(), true))
			{
				auto filePath = _fe3d.audioEntity_getFilePath("@" + arguments[0].getString());
				_fe3d.music_addToPlaylist(filePath);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:music_clear_playlist") // Clear music playlist
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.music_clearPlaylist();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:music_set_volume") // Set music volume
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.music_setVolume(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:music_get_volume") // Get music volume
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.music_getVolume();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:music_is_playing") // Check if music is playing
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.music_isPlaying();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:music_pause") // Pause music
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.music_pause();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:music_is_paused") // Check if music is paused
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.music_isPaused();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:music_resume") // Resume music
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.music_resume();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}