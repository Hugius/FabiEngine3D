#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dModelGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:model_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview model
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.modelEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview model
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full modelEntity IDs based on part ID
			for (const auto& ID : _fe3d.modelEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview models
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:model_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.modelEntity_getAllIDs();

			// For every model
			for (const auto& ID : result)
			{
				// Only non-preview models
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_is_visible")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_position")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getBasePosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getBaseRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation_origin")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getBaseRotationOrigin(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_size")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getBaseSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_color")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				//auto result = _fe3d.modelEntity_getColor(arguments[0].getString());
				//returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_min_height")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_max_height")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_lightness")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				//auto result = _fe3d.modelEntity_getLightness(arguments[0].getString());
				//returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_get_alpha")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				//auto result = _fe3d.modelEntity_getAlpha(arguments[0].getString());
				//returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute model functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:model` functionality as a networking server!");
	}

	// Return
	return true;
}