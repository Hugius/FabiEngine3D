#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound3dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sound3d_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString().find('@') != string::npos)
			{
				_throwScriptError("id of requested sound with id \"" + args[0].getString() + "\" cannot contain '@'");
				return true;
			}

			const auto result = _fe3d->sound3d_isExisting(args[0].getString());

			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound3d_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0].getString().find('@') != string::npos)
			{
				_throwScriptError("id of requested sound with id \"" + args[0].getString() + "\" cannot contain '@'");
				return true;
			}

			for(const auto& id : _fe3d->sound3d_getIds())
			{
				if(args[0].getString() == id.substr(0, args[0].getString().size()))
				{
					if(id[0] != '@')
					{
						returnValues.push_back(ScriptValue(SVT::STRING, id));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->sound3d_getIds();

			for(const auto& id : result)
			{
				if(id[0] != '@')
				{
					returnValues.push_back(ScriptValue(SVT::STRING, id));
				}
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_started")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_isStarted(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_playing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_isPlaying(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_paused")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_isPaused(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_volume")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getVolume(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0].getString()).x;

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0].getString()).y;

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0].getString()).z;

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_max_volume")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getMaxVolume(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_max_distance")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0].getString(), false))
			{
				const auto result = _fe3d->sound3d_getMaxDistance(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sound3d` functionality as networking server!");
	}

	return true;
}