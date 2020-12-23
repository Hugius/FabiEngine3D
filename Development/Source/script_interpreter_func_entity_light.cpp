#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dLightEntity(const string& ID)
{
	// Just to be consistent with not starting entity ID's with '@'
	if (ID.front() == '@')
	{
		_throwScriptError("Requested light ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.lightEntity_isExisting(ID))
	{
		_throwScriptError("Requested light with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dLightEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:light_is_existing") // Get lightEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Check if existing
			auto result = _fe3d.lightEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:light_place") // Create lightEntity
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Size
			ScriptValueType::DECIMAL, // Intensity
			ScriptValueType::DECIMAL // Distance
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New light ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New light ID cannot start with '@'");
				return true;
			}

			// Check if light entity already exists
			if (_fe3d.lightEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Light with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Add light
			_fe3d.lightEntity_add(arguments[0].getString(),
				Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()),
				Vec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()),
				arguments[7].getDecimal(),
				arguments[8].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:light_delete") // Delete lightEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				_fe3d.lightEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:light_set_position") // Set lightEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				_fe3d.lightEntity_setPosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:light_get_position") // Get lightEntity position
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:light_set_color") // Set lightEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				_fe3d.lightEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:light_get_color") // Get lightEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:light_set_intensity") // Set lightEntity intensity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				_fe3d.lightEntity_setIntensity(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:light_get_intensity") // Get lightEntity intensity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getIntensity(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:light_set_distance") // Set lightEntity distance
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				_fe3d.lightEntity_setDistanceFactor(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:light_get_distance") // Get lightEntity distance
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLightEntity(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getDistanceFactor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}