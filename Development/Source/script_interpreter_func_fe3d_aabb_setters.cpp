#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAabbSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:aabb_place")
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Size
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// New AABB ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("new AABB ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if AABB entity already exists
			if (_fe3d.aabbEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("AABB with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Place AABB
			_fe3d.aabbEntity_create(arguments[0].getString());
			_fe3d.aabbEntity_setBasePosition(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.aabbEntity_setBaseSize(arguments[0].getString(), Vec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabb_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot delete a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot delete AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Delete AABB
				_fe3d.aabbEntity_delete(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_visible")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set visibility
				_fe3d.aabbEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set position
				_fe3d.aabbEntity_setBasePosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set size
				_fe3d.aabbEntity_setBaseSize(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Move position
				_fe3d.aabbEntity_move(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_scale")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Scale size
				_fe3d.aabbEntity_scale(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_move_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Move position
				_fe3d.aabbEntity_moveTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_scale_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Scale size
				_fe3d.aabbEntity_scaleTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_raycast_responsive")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set responsiveness
				_fe3d.aabbEntity_setRaycastResponsive(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_collision_responsive")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set responsiveness
				_fe3d.aabbEntity_setCollisionResponsive(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute AABB functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:aabb` functionality as a networking server!");
	}

	// Return
	return true;
}