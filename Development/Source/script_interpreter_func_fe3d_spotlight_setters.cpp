#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dSpotlightSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:spotlight_place")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			const auto ID = arguments[0].getString();

			// @ sign is reserved
			if(ID.front() == '@')
			{
				_throwScriptError("new spotlight ID (\"" + ID + "\") cannot start with '@'");
				return true;
			}

			// Check if spotlight entity already exists
			if(_fe3d.spotlightEntity_isExisting(ID))
			{
				_throwScriptError("spotlight with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create spotlight
			_fe3d.spotlightEntity_create(ID);
			_fe3d.spotlightEntity_setPosition(ID, Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.spotlightEntity_setColor(ID, Vec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));
			_fe3d.spotlightEntity_setYaw(ID, arguments[7].getDecimal());
			_fe3d.spotlightEntity_setPitch(ID, arguments[8].getDecimal());
			_fe3d.spotlightEntity_setIntensity(ID, arguments[9].getDecimal());
			_fe3d.spotlightEntity_setAngle(ID, arguments[10].getDecimal());
			_fe3d.spotlightEntity_setDistance(ID, arguments[11].getDecimal());

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:spotlight_delete")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_visible")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_position")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setPosition(arguments[0].getString(),
												  Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_move(arguments[0].getString(),
										   Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_move_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_moveTo(arguments[0].getString(),
											 Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_color")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setColor(arguments[0].getString(),
											   Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_yaw")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setYaw(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_pitch")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setPitch(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_intensity")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setIntensity(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_angle")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setAngle(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_set_distance")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				_fe3d.spotlightEntity_setDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute spotlight functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:spotlight` functionality as a networking server!");
	}

	// Return
	return true;
}