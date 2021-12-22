#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSpotlightSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:spotlight_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			const auto ID = arguments[0].getString();

			// @ sign not allowed
			if(ID[0] == '@')
			{
				_throwScriptError("new spotlight ID (\"" + ID + "\") cannot contain '@'");
				return true;
			}

			// Check if spotlight entity already exists
			if(_fe3d.spotlight_isExisting(ID))
			{
				_throwScriptError("spotlight with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create spotlight
			_fe3d.spotlight_create(ID);
			_fe3d.spotlight_setPosition(ID, fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.spotlight_setColor(ID, fvec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));
			_fe3d.spotlight_setYaw(ID, arguments[7].getDecimal());
			_fe3d.spotlight_setPitch(ID, arguments[8].getDecimal());
			_fe3d.spotlight_setIntensity(ID, arguments[9].getDecimal());
			_fe3d.spotlight_setAngle(ID, arguments[10].getDecimal());
			_fe3d.spotlight_setDistance(ID, arguments[11].getDecimal());

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:spotlight_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through spotlights
			for(const auto& ID : _fe3d.spotlight_getIDs())
			{
				// @ sign not allowed
				if(ID[0] != '@')
				{
					_fe3d.spotlight_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:spotlight_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setPosition(arguments[0].getString(),
											fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_move(arguments[0].getString(),
									 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_moveTo(arguments[0].getString(),
									   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setColor(arguments[0].getString(),
										 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_yaw")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setYaw(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_pitch")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setPitch(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setIntensity(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_angle")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setAngle(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_distance")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlight_setDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:spotlight` functionality as networking server!");
	}

	// Return
	return true;
}