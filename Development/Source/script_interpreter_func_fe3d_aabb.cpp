#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dAabbEntity(const string& ID)
{
	// Cannot request/delete a preview entity
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested AABB with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.aabbEntity_isExisting(ID))
	{
		_throwScriptError("requested AABB with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dAabbEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:aabb_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot access a bound entity
			if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
			{
				_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
				return true;
			}

			// Check if existing
			auto result = _fe3d.aabbEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:aabb_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested AABB with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full aabbEntity IDs based on part ID
			for (const auto& ID : _fe3d.aabbEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview AABBs
					if (ID.front() != '@')
					{
						// Only non-bound AABBs
						if (!_fe3d.aabbEntity_hasParent(ID))
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
						}
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.aabbEntity_getAllIDs();

			// For every AABB
			for (const auto& ID : result)
			{
				// Only non-preview AABBs
				if (ID.front() != '@')
				{
					// Only non-bound AABBs
					if (!_fe3d.aabbEntity_hasParent(ID))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:aabb_place")
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Size
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
			_fe3d.aabbEntity_setPosition(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.aabbEntity_setSize(arguments[0].getString(), Vec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabb_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot delete a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot delete AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
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
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Set visibility
				_fe3d.aabbEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_is_visible")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Get visibility
				auto result = _fe3d.aabbEntity_isVisible(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Set position
				_fe3d.aabbEntity_setPosition(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				
				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Move position
				_fe3d.aabbEntity_move(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_position")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Get position
				auto result = _fe3d.aabbEntity_getPosition(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Set size
				_fe3d.aabbEntity_setSize(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_scale")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Scale size
				_fe3d.aabbEntity_scale(arguments[0].getString(), Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_size")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
					return true;
				}

				// Get size
				auto result = _fe3d.aabbEntity_getSize(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_set_raycast_responsive")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
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
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing AABB ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to a model or billboard!");
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

	return true;
}
