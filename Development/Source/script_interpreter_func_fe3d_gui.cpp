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

			// Check if game entity already exists
			if (_fe3d.guiEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("image with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Compose full texture path
			auto texturePath = string("user\\assets\\textures\\gui_maps\\") + arguments[1].getString();

			// Calculate size in viewport
			auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) / 
				Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
			auto size = Vec2(arguments[5].getDecimal(), arguments[6].getDecimal()) * sizeMultiplier;

			// Calculate position in viewport
			auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
				Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
			auto position = Vec2(arguments[2].getDecimal(), arguments[3].getDecimal()) * sizeMultiplier;
			auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
			position += Vec2(fabsf(offset.x), fabsf(offset.y));
			
			// Add image
			_fe3d.guiEntity_add(
				arguments[0].getString(),
				texturePath,
				position,
				arguments[4].getDecimal(),
				size,
				true);
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
				_fe3d.guiEntity_setPosition(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
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
				_fe3d.guiEntity_move(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
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
				auto result = _fe3d.guiEntity_getPosition(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
				auto result = _fe3d.guiEntity_getPosition(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
				_fe3d.guiEntity_setSize(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
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
				_fe3d.guiEntity_scale(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
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
				auto result = _fe3d.guiEntity_getSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
				auto result = _fe3d.guiEntity_getSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
	else if (functionName == "fe3d:image_get_all_names") // Get all guiEntity names
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.guiEntity_getAllIDs();

			// For every image
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
	else
	{
		return false;
	}

	return true;
}