#include "script_interpreter.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dPointlightSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:pointlight_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->pointlight_isExisting(args[0].getString()))
			{
				_throwScriptError("pointlight already exists!");
				return true;
			}

			_fe3d->pointlight_create(args[0].getString());
			_fe3d->pointlight_setPosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
			_fe3d->pointlight_setRadius(args[0].getString(), fvec3(args[4].getDecimal(), args[5].getDecimal(), args[6].getDecimal()));
			_fe3d->pointlight_setColor(args[0].getString(), fvec3(args[7].getDecimal(), args[8].getDecimal(), args[9].getDecimal()));
			_fe3d->pointlight_setIntensity(args[0].getString(), args[10].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:pointlight_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->pointlight_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->pointlight_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:pointlight_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_setPosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_move(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_moveTo(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_radius")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_setRadius(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_setColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				_fe3d->pointlight_setIntensity(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_shape")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				if(args[1].getString() == "CIRCLE")
				{
					_fe3d->pointlight_setShape(args[0].getString(), PointlightShape::CIRCLE);
					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else if(args[1].getString() == "SQUARE")
				{
					_fe3d->pointlight_setShape(args[0].getString(), PointlightShape::SQUARE);
					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else
				{
					Logger::throwWarning("invalid shape!");
					returnValues.push_back(ScriptValue(SVT::EMPTY));
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
		_throwScriptError("cannot access `fe3d:pointlight` functionality as networking server!");
	}

	return true;
}