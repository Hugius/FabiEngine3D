#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAabbGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:aabb_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:aabb_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot access a bound entity
			if (!_fe3d.aabbEntity_getParentID(arguments[0].getString()).empty())
			{
				_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
				return true;
			}

			// Check if existing
			auto result = _fe3d.aabbEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:aabb_is_visible")
	{
		auto types = { ScriptValueType::STRING };

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

				// Get visibility
				auto result = _fe3d.aabbEntity_isVisible(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_position")
	{
		auto types = { ScriptValueType::STRING };

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

				// Get position
				auto result = _fe3d.aabbEntity_getPosition(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_size")
	{
		auto types = { ScriptValueType::STRING };

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

				// Get size
				auto result = _fe3d.aabbEntity_getSize(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:aabb_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
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