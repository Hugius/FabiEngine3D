#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dTextEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("Requested text ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.textEntity_isExisting(ID))
	{
		_throwScriptError("Requested text with ID \"" + ID + "\" does not exist!");

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dTextEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:text_is_existing") // Get textEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested text ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.textEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:text_find_ids") // Find full textEntity IDs
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested text ID cannot start with '@'");
				return true;
			}

			// Find full textEntity IDs based on part ID
			for (auto& ID : _fe3d.textEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview text
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:text_get_all_ids") // Get all textEntity IDs
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.textEntity_getAllIDs();

			// For every text
			for (auto& ID : result)
			{
				// Only non-preview texts
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:text_place") // Create textEntity
	{
		auto types =
		{
			ScriptValueType::STRING, // ID
			ScriptValueType::STRING, // Font path
			ScriptValueType::STRING, // Text
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, // Position
			ScriptValueType::DECIMAL, // Rotation
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Size
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New text ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New text ID cannot start with '@'");
				return true;
			}

			// Check if text entity already exists
			if (_fe3d.textEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Text with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Compose full texture path
			auto fontPath = string("user\\assets\\fonts\\") + arguments[1].getString();

			// Calculate size in viewport
			auto sizeMultiplier = Vec2(_fe3d.misc_getViewportSize()) /
				Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
			auto size = Vec2(arguments[6].getDecimal(), arguments[7].getDecimal()) * sizeMultiplier;

			// Calculate position in viewport
			auto positionMultiplier = Vec2(_fe3d.misc_getViewportPosition()) /
				Vec2(static_cast<float>(_fe3d.misc_getWindowWidth()), static_cast<float>(_fe3d.misc_getWindowHeight()));
			auto position = Vec2(arguments[3].getDecimal(), arguments[4].getDecimal()) * sizeMultiplier;
			auto offset = Vec2(1.0f) - Vec2((positionMultiplier.x * 2.0f) + sizeMultiplier.x, (positionMultiplier.y * 2.0f) + sizeMultiplier.y);
			position += Vec2(fabsf(offset.x), fabsf(offset.y));

			// Add text
			_fe3d.textEntity_add(
				arguments[0].getString(),
				arguments[2].getString(),
				fontPath,
				Vec3(1.0f),
				position,
				arguments[5].getDecimal(),
				size,
				true,
				true);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:text_delete") // Delete textEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_visible") // Set textEntity visibility
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				// Determine if text must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.textEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.textEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_is_visible") // Get textEntity visibility
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_position") // Set textEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setPosition(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_move") // Move textEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_move(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_position_x") // Get textEntity position X
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getPosition(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_get_position_y") // Get textEntity position Y
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getPosition(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_rotation") // Set textEntity rotation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_rotate") // Rotate textEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_rotation") // Get textEntity rotation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_size") // Set textEntity size
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setSize(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_scale") // Scale textEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_scale(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_width") // Get textEntity width
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_get_height") // Get textEntity height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_color") // Set textEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_color") // Get textEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_content") // Set textEntity content
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setTextContent(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_content") // Get textEntity content
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getTextContent(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_alpha") // Set textEntity alpha
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_alpha") // Get textEntity alpha
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getAlpha(arguments[0].getString());
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