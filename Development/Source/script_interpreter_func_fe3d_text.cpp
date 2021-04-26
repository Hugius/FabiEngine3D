#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dTextEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("requested text ID cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.textEntity_isExisting(ID))
	{
		_throwScriptError("requested text with ID \"" + ID + "\" does not exist!");

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dTextEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:text_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("requested text ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.textEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:text_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("requested text ID cannot start with '@'");
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
	else if (functionName == "fe3d:text_get_all_ids")
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
	else if (functionName == "fe3d:text_place")
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
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// New text ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("new text ID cannot start with '@'");
				return true;
			}

			// Check if text entity already exists
			if (_fe3d.textEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("text with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Compose full texture path
			auto fontPath = string("game_assets\\fonts\\") + arguments[1].getString();

			// Add text
			_fe3d.textEntity_add(
				arguments[0].getString(),
				arguments[2].getString(),
				fontPath,
				Vec3(1.0f),
				_convertGuiPositionToViewport(Vec2(arguments[3].getDecimal(), arguments[4].getDecimal())),
				arguments[5].getDecimal(),
				_convertGuiSizeToViewport(Vec2(arguments[6].getDecimal(), arguments[7].getDecimal())),
				true,
				true);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));

			// In-engine viewport boundaries
			if (!_fe3d.engine_isGameExported())
			{
				auto minPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition()));
				auto maxPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition() + _fe3d.misc_getViewportSize()));
				_fe3d.textEntity_setMinPosition(arguments[0].getString(), minPos);
				_fe3d.textEntity_setMaxPosition(arguments[0].getString(), maxPos);
			}
		}
	}
	else if (functionName == "fe3d:text_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_visible")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:text_is_visible")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				Vec2 position = _convertGuiPositionToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_move(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_position_x")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:text_get_position_y")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:text_set_rotation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_rotate")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_rotation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				Vec2 size = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_scale")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_scale(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_width")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:text_get_height")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:text_set_color")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:text_get_color")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_content")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setTextContent(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_content")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				auto result = _fe3d.textEntity_getTextContent(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
			}
		}
	}
	else if (functionName == "fe3d:text_set_alpha")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dTextEntity(arguments[0].getString()))
			{
				_fe3d.textEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_get_alpha")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
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