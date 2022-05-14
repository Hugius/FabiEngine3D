#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound2dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:sound2d_place")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->sound2d_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("sound2D already exists");

				return true;
			}

			if(_validateFe3dSound2d(args[1]->getString(), true))
			{
				_duplicator->copyTemplateSound2d(args[0]->getString(), ("@" + args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				_fe3d->sound2d_delete(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & sound2dId : _fe3d->sound2d_getIds())
			{
				if(sound2dId[0] != '@')
				{
					_fe3d->sound2d_delete(sound2dId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound2d_start")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
			{
				_throwRuntimeError("sound2D is already started");

				return true;
			}

			if((args[1]->getInteger() == 0) || (args[1]->getInteger() < -1))
			{
				_throwRuntimeError("play count is invalid");

				return true;
			}

			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				_fe3d->sound2d_start(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_pause")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				if(_fe3d->sound2d_isPaused(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is already paused");

					return true;
				}

				_fe3d->sound2d_pause(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_resume")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				if(!_fe3d->sound2d_isPaused(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not paused");

					return true;
				}

				_fe3d->sound2d_resume(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_stop")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				_fe3d->sound2d_stop(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_set_volume")
	{
		const auto types = {SVT::STRING, SVT::INTEGER, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				_fe3d->sound2d_setVolume(args[0]->getString(), args[1]->getInteger(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_set_left_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				_fe3d->sound2d_setLeftIntensity(args[0]->getString(), args[1]->getInteger(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_set_right_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				_fe3d->sound2d_setRightIntensity(args[0]->getString(), args[1]->getInteger(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
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