#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dPointlightSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:pointlight_place")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->pointlight_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("pointlight already exists");

				return true;
			}

			if(_fe3d->pointlight_getIds().size() == _fe3d->pointlight_getMaxCount())
			{
				_throwRuntimeError("pointlight maximum is reached");

				return true;
			}

			if(_validateFe3dPointlight(args[1]->getString(), true))
			{
				_duplicator->copyTemplatePointlight(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->pointlight_setPosition(args[0]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_duplicator->deleteCopiedPointlight(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & pointlightId : _fe3d->pointlight_getIds())
			{
				if(pointlightId[0] != '@')
				{
					_duplicator->deleteCopiedPointlight(pointlightId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:pointlight_set_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_setVisible(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_setPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_move(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_moveTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_radius")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_setRadius(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_setColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_intensity")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				_fe3d->pointlight_setIntensity(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_shape")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0]->getString(), false))
			{
				if(args[1]->getString() == "CIRCLE")
				{
					_fe3d->pointlight_setShape(args[0]->getString(), PointlightShapeType::CIRCLE);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "SQUARE")
				{
					_fe3d->pointlight_setShape(args[0]->getString(), PointlightShapeType::SQUARE);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else
				{
					_throwRuntimeError("shape is invalid");

					return true;
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:pointlight` functionality as a networking server");

		return true;
	}

	return true;
}