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
				_throwRuntimeError("clock is not existing");

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
				_throwRuntimeError("clock is not existing");

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
				_throwRuntimeError("clock is not existing");

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