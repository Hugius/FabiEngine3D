#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSoundSetterFunction2D(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:sound_2d_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("new sound ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if sound already exists
			if(_fe3d.sound2D_isExisting(arguments[0].getString()))
			{
				_throwScriptError("sound with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview sound ID
			if(_validateFe3dSound2D("@" + arguments[1].getString(), true))
			{
				auto filePath = _fe3d.sound2D_getFilePath("@" + arguments[1].getString());
				_fe3d.sound2D_create(arguments[0].getString(), filePath);
				_fe3d.sound2D_setVolume(arguments[0].getString(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_play")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), false);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_play_forced")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), true);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_pause")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_pause(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_pause_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound2D_pauseAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_2d_resume")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_resume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_resume_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound2D_resumeAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_2d_stop")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_stop(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound_2d_stop_all")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound2D_stopAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound_2d_set_volume")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSound2D(arguments[0].getString(), false))
			{
				_fe3d.sound2D_setVolume(arguments[0].getString(), arguments[1].getDecimal());
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
		_throwScriptError("cannot access `fe3d:sound_2d` functionality as networking server!");
	}

	return true;
}