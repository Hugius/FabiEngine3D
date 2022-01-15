#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSpotlightSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:spotlight_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->spotlight_isExisting(args[0].getString()))
			{
				_throwScriptError("spotlight already exists!");
				return true;
			}

			_fe3d->spotlight_create(args[0].getString());
			_fe3d->spotlight_setPosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
			_fe3d->spotlight_setColor(args[0].getString(), fvec3(args[4].getDecimal(), args[5].getDecimal(), args[6].getDecimal()));
			_fe3d->spotlight_setYaw(args[0].getString(), args[7].getDecimal());
			_fe3d->spotlight_setPitch(args[0].getString(), args[8].getDecimal());
			_fe3d->spotlight_setIntensity(args[0].getString(), args[9].getDecimal());
			_fe3d->spotlight_setAngle(args[0].getString(), args[10].getDecimal());
			_fe3d->spotlight_setDistance(args[0].getString(), args[11].getDecimal());

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:spotlight_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->spotlight_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->spotlight_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:spotlight_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setPosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_move(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_moveTo(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_yaw")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setYaw(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_pitch")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setPitch(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setIntensity(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_angle")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setAngle(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_distance")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSpotlight(args[0].getString()))
			{
				_fe3d->spotlight_setDistance(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:spotlight` functionality as networking server!");
	}

	return true;
}