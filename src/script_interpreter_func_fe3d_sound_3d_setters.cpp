#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSoundSetterFunction3D(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:sound_3d_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			string newID = arguments[0].getString();
			string previewID = arguments[1].getString();

			// @ sign is reserved
			if(newID.front() == '@')
			{
				_throwScriptError("new sound ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if sound already exists
			if(_fe3d.sound3D_isExisting(newID))
			{
				_throwScriptError("sound with ID \"" + newID + "\" already exists!");
				return true;
			}

			// Validate preview sound ID
			if(_validateFe3dSound3D("@" + previewID, true))
			{
				// Temporary values
				auto position = fvec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal());
				auto maxVolume = arguments[5].getDecimal();
				auto maxDistance = arguments[6].getDecimal();

				// Add sound
				_worldEditor.copyPreviewSound(newID, ("@" + previewID), position);
				_fe3d.sound3D_setMaxVolume(newID, maxVolume);
				_fe3d.sound3D_setMaxDistance(newID, maxDistance);

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_play")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), false);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_play_forced")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), true);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_pause")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_pause(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_pause_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_pauseAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_3d_resume")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_resume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_resume_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_resumeAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_3d_stop")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_stop(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_stop_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_stopAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_3d_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setPosition(
					arguments[0].getString(),
					fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_set_max_volume")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setMaxVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_3d_set_max_distance")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setMaxDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sound functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sound_3d` functionality as networking server!");
	}

	return true;
}