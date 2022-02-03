#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound2dGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:sound2d_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString().find('@') != string::npos)
			{
				_throwRuntimeError("id of requested sound with id \"" + args[0]->getString() + "\" cannot contain '@'");
				return true;
			}

			const auto result = _fe3d->sound2d_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound2d_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString().find('@') != string::npos)
			{
				_throwRuntimeError("id of requested sound with id \"" + args[0]->getString() + "\" cannot contain '@'");
				return true;
			}

			for(const auto& id : _fe3d->sound2d_getIds())
			{
				if(args[0]->getString() == id.substr(0, args[0]->getString().size()))
				{
					if(id[0] != '@')
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, id));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->sound2d_getIds();

			for(const auto& id : result)
			{
				if(id[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, id));
				}
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_started")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_isStarted(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_playing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_isPlaying(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_paused")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_isPaused(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_volume")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_getVolume(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:sound2d` functionality as a networking server");
		return true;
	}

	return true;
}