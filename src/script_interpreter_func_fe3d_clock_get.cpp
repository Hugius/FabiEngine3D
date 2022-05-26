#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClockGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:clock_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");

				return true;
			}

			const auto result = _fe3d->clock_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->clock_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:clock_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->clock_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:clock_is_started")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");

				return true;
			}

			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock does not exist");

				return true;
			}

			const auto result = _fe3d->clock_isStarted(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_is_paused")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");

				return true;
			}

			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock does not exist");

				return true;
			}

			if(!_fe3d->clock_isStarted(args[0]->getString()))
			{
				_throwRuntimeError("clock is not started");

				return true;
			}

			const auto result = _fe3d->clock_isPaused(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:clock_get_delta")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");

				return true;
			}

			if(!_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock does not exist");

				return true;
			}

			if(_fe3d->clock_isStarted(args[0]->getString()))
			{
				_throwRuntimeError("clock is still started");

				return true;
			}

			const auto result = _fe3d->clock_getDeltaTime(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}