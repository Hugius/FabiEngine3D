#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dGameEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:model_is_existing") // Get gameEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested model ID cannot start with '@'");
			}

			// Check if existing
			auto result = _fe3d.gameEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:model_place") // Create gameEntity
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL
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

			// Validate preview model ID
			if (_validateFe3dGameEntity("@" + arguments[1].getString(), true))
			{
				_sceneEditor.placeModel(arguments[0].getString(), "@" + arguments[1].getString(),
					Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_delete") // Delete gameEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_delete_all") // Delete all gameEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// For every model
			for (const auto& ID : _fe3d.gameEntity_getAllIDs())
			{
				// Only non-preview models
				if (ID.front() != '@')
				{
					_fe3d.gameEntity_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_set_visible") // Set gameEntity visibility
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				// Determine if model must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.gameEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.gameEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_is_visible") // Get gameEntity visibility
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_all_visible") // Set ALL gameEntities visibility
	{
		auto types = { ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// For every model
			for (const auto& ID : _fe3d.gameEntity_getAllIDs())
			{
				// Only non-preview models
				if (ID.front() != '@')
				{
					// Determine if model must be visible or not
					if (arguments[0].getBoolean())
					{
						_fe3d.gameEntity_show(ID);
					}
					else
					{
						_fe3d.gameEntity_hide(ID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:model_get_all_names") // Get ALL gameEntities visibility
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gameEntity_getAllIDs();

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
	else if (functionName == "fe3d:model_set_position") // Set gameEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setPosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_move") // Move gameEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_move(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_position") // Get gameEntity position
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation_origin") // Set gameEntity rotation oriign
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setRotationOrigin(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation_origin") // Get gameEntity rotation origin
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getRotationOrigin(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation") // Set gameEntity rotation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setRotation(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_rotate") // Rotate gameEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_rotate(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_rotation") // Get gameEntity rotation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_size") // Set gameEntity size
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setSize(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_scale") // Scale gameEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_scale(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_size") // Get gameEntity size
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_color") // Set gameEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_color") // Get gameEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_max_height") // Set gameEntity maximum height
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_max_height") // Get gameEntity maximum height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_lightness") // Set gameEntity lightness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				_fe3d.gameEntity_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_get_lightness") // Get gameEntity lightness
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				auto result = _fe3d.gameEntity_getLightness(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:model_set_aabb_responsive") // Set gameEntity AABB responsiveness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dGameEntity(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false);

				// Check if gameEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("Model has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for (auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setResponsive(ID, arguments[1].getBoolean());
				}
				
				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}