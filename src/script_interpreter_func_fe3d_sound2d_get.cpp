#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sound2d_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString().find('@') != string::npos)
			{
				_throwScriptError("ID of requested sound with ID \"" + args[0].getString() + "\" cannot contain '@'");
				return true;
			}

			auto result = _fe3d.sound2d_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound2d_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString().find('@') != string::npos)
			{
				_throwScriptError("ID of requested sound with ID \"" + args[0].getString() + "\" cannot contain '@'");
				return true;
			}

			for(const auto& ID : _fe3d.sound2d_getIDs())
			{
				if(args[0].getString() == ID.substr(0, args[0].getString().size()))
				{
					if(ID[0] != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d.sound2d_getIDs();

			for(const auto& ID : result)
			{
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_started")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0].getString(), false))
			{
				auto result = _fe3d.sound2d_isStarted(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_playing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0].getString(), false))
			{
				auto result = _fe3d.sound2d_isPlaying(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_paused")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0].getString(), false))
			{
				auto result = _fe3d.sound2d_isPaused(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_volume")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0].getString(), false))
			{
				auto result = _fe3d.sound2d_getVolume(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sound2d` functionality as networking server!");
	}

	return true;
}