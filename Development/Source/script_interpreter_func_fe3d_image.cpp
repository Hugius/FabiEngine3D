#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dGuiEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("Requested image ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.guiEntity_isExisting(ID))
	{
		_throwScriptError("Requested image with ID \"" + ID + "\" does not exist!");

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dGuiEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:image_is_existing") // Get guiEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested image ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.guiEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:image_find_ids") // Find full guiEntity IDs
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested image ID cannot start with '@'");
				return true;
			}

			// Find full guiEntity IDs based on part ID
			for (auto& ID : _fe3d.guiEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview images
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:image_get_all_ids") // Get all guiEntity IDs
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.guiEntity_getAllIDs();

			// For every image
			for (auto& ID : result)
			{
				// Only non-preview images
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:image_place") // Create guiEntity
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::STRING, // Texture path
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, // Rotation
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Size
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New image ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New image ID cannot start with '@'");
				return true;
			}

			// Check if guiEntity already exists
			if (_fe3d.guiEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("image with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}
			
			// Add image
			_fe3d.guiEntity_add(
				arguments[0].getString(),
				string("game_assets\\textures\\image_maps\\") + arguments[1].getString(),
				_convertGuiPositionToViewport(Vec2(arguments[2].getDecimal(), arguments[3].getDecimal())),
				arguments[4].getDecimal(),
				_convertGuiSizeToViewport(Vec2(arguments[5].getDecimal(), arguments[6].getDecimal())),
				true);

			// In-engine viewport boundaries
			if (!_fe3d.engine_isGameExported())
			{
				auto minPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition()));
				auto maxPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition() + _fe3d.misc_getViewportSize()));
				_fe3d.guiEntity_setMinPosition(arguments[0].getString(), minPos);
				_fe3d.guiEntity_setMaxPosition(arguments[0].getString(), maxPos);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:image_delete") // Delete guiEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_visible") // Set guiEntity visibility
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				// Determine if image must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.guiEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.guiEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_is_visible") // Get guiEntity visibility
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_position") // Set guiEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				Vec2 position = _convertGuiPositionToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.guiEntity_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move") // Move guiEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.guiEntity_move(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_position_x") // Get guiEntity position X
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:image_get_position_y") // Get guiEntity position Y
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:image_set_rotation") // Set guiEntity rotation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate") // Rotate guiEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_rotation") // Get guiEntity rotation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_size") // Set guiEntity size
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				Vec2 size = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.guiEntity_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale") // Scale guiEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.guiEntity_scale(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_width") // Get guiEntity width
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:image_get_height") // Get guiEntity height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:image_set_color") // Set guiEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_color") // Get guiEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_alpha") // Set guiEntity alpha
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_alpha") // Get guiEntity alpha
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getAlpha(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:image_start_animation") // Start guiEntity sprite animation
	{
		auto types =
		{
			ScriptValueType::STRING,
			ScriptValueType::INTEGER,
			ScriptValueType::INTEGER,
			ScriptValueType::INTEGER,
			ScriptValueType::INTEGER
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				_fe3d.guiEntity_setAnimationRows(arguments[0].getString(), arguments[1].getInteger());
				_fe3d.guiEntity_setAnimationColumns(arguments[0].getString(), arguments[2].getInteger());
				_fe3d.guiEntity_setAnimationFramestep(arguments[0].getString(), arguments[3].getInteger());
				_fe3d.guiEntity_playSpriteAnimation(arguments[0].getString(), arguments[4].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_is_animation_playing") // Check if guiEntity sprite animation is playing
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_isAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_stop_animation") // Stop guiEntity sprite animation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_getAlpha(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:image_is_animation_finished") // Check if guiEntity sprite animation is finished
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dGuiEntity(arguments[0].getString()))
			{
				auto result = _fe3d.guiEntity_isAnimationFinished(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}