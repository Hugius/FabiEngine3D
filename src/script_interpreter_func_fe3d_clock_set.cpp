#include "script_interpreter.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClockSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:clock_create")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->clock_isIdReserved(args[0]->getString()))
			{
				_throwRuntimeError("clock ID is reserved");
				return true;
			}
			if(_fe3d->clock_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("clock is already existing");
				return true;
			}

			_fe3d->clock_create(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:clock_delete")
	{
		auto types = {SVT::STRING};

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

			_fe3d->clock_delete(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:clock_start")
	{
		auto types = {SVT::STRING};

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
				_throwRuntimeError("clock is already started");
				return true;
			}

			_fe3d->clock_start(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:clock_pause")
	{
		auto types = {SVT::STRING};

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
			if(_fe3d->clock_isPaused(args[0]->getString()))
			{
				_throwRuntimeError("clock is already paused");
				return true;
			}

			_fe3d->clock_pause(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:clock_resume")
	{
		auto types = {SVT::STRING};

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
			if(!_fe3d->clock_isPaused(args[0]->getString()))
			{
				_throwRuntimeError("clock is not paused");
				return true;
			}

			_fe3d->clock_pause(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:clock_stop")
	{
		auto types = {SVT::STRING};

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

			_fe3d->clock_stop(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}