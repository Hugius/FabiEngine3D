#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCaptorSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:captor_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->captor_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("captor already exists");
				return true;
			}

			_fe3d->captor_create(args[0]->getString());
			_fe3d->captor_setPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:captor_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_delete(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & id : _fe3d->captor_getIds())
			{
				if(id[0] != '@')
				{
					_fe3d->captor_delete(id);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:captor_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_setVisible(args[0]->getString(), args[1]->getBoolean());
				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_setPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_move(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_moveTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_capture")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_capture(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:captor_set_exception_entity_id")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dCaptor(args[0]->getString()))
			{
				_fe3d->captor_setExceptionEntityId(args[0]->getString(), args[1]->getString());

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
		_throwRuntimeError("cannot access `fe3d:captor` functionality as a networking server");
		return true;
	}

	return true;
}