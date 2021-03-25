#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dModelEntity(const string& ID, bool previewEntity)
{
	// Cannot request/delete a preview entity
	if (!previewEntity && ID.front() == '@')
	{
		_throwScriptError("Requested model ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.modelEntity_isExisting(ID))
	{
		if (previewEntity)
		{
			_throwScriptError("Requested model with ID \"" + ID.substr(1) + "\" does not exist!");
		}
		else
		{
			_throwScriptError("Requested model with ID \"" + ID + "\" does not exist!");
		}

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dModelEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:model_is_existing") // Get modelEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested model ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.modelEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_find_ids") // Find full modelEntity IDs
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested model ID cannot start with '@'");
				return true;
			}

			// Find full modelEntity IDs based on part ID
			for (auto& ID : _fe3d.modelEntity_getAllIDs())
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
	else if (functionName == "fe3d:model_get_all_ids") // Get all modelEntity IDs
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.modelEntity_getAllIDs();

			// For every model
			for (auto& ID : result)
			{
				// Only non-preview models
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_place") // Create modelEntity
	{
		auto types =
		{
			ScriptValueType::STRING, // New modelEntity ID
			ScriptValueType::STRING, // Preview modelEntity ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Position
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New model ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New model ID cannot start with '@'");
				return true;
			}

			// Check if modelEntity already exists
			if (_fe3d.modelEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Model with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview model ID
			if (_validateFe3dModelEntity("@" + arguments[1].getString(), true))
			{
				_sceneEditor.copyPreviewModel(arguments[0].getString(), "@" + arguments[1].getString(),
					Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_delete") // Delete modelEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_visible") // Set modelEntity visibility
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Determine if model must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.modelEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.modelEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_is_visible") // Get modelEntity visibility
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_position") // Set modelEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setPosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_move") // Move modelEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_move(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_position") // Get modelEntity position
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation_origin") // Set modelEntity rotation oriign
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setRotationOrigin(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation_origin") // Get modelEntity rotation origin
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getRotationOrigin(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation") // Set modelEntity rotation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setRotation(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_rotate") // Rotate modelEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_rotate(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation") // Get modelEntity rotation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_size") // Set modelEntity size
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setSize(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_scale") // Scale modelEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_scale(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_size") // Get modelEntity size
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_color") // Set modelEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_color") // Get modelEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_min_height") // Set modelEntity minimum height
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_min_height") // Get modelEntity minimum height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_max_height") // Set modelEntity maximum height
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_max_height") // Get modelEntity maximum height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_lightness") // Set modelEntity lightness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_lightness") // Get modelEntity lightness
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getLightness(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_aabb_raycast_responsive") // Set modelEntity AABB raycasting responsiveness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false);

				// Check if modelEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("Model has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for (auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, arguments[1].getBoolean());
				}
				
				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_aabb_collision_responsive") // Set modelEntity AABB collision responsiveness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false);

				// Check if modelEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("Model has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for (auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setCollisionResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_alpha") // Set modelEntity alpha
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_fe3d.modelEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_alpha") // Get modelEntity alpha
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _fe3d.modelEntity_getAlpha(arguments[0].getString());
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