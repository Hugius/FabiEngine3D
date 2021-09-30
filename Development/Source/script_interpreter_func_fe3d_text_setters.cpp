#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dTextSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:text_place")
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
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values 
			const auto ID = arguments[0].getString();

			// New text ID cannot start with '@'
			if (ID.front() == '@')
			{
				_throwScriptError("new text ID \"" + ID + "\" cannot start with '@'");
				return true;
			}

			// Check if text entity already exists
			if (_fe3d.textEntity_isExisting(ID))
			{
				_throwScriptError("text with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create text
			_fe3d.textEntity_create(ID, true, true);
			_fe3d.textEntity_setPosition(ID, _convertGuiPositionToViewport(Vec2(arguments[3].getDecimal(), arguments[4].getDecimal())));
			_fe3d.textEntity_setRotation(ID, arguments[5].getDecimal());
			_fe3d.textEntity_setSize(ID, _convertGuiSizeToViewport(Vec2(arguments[6].getDecimal(), arguments[7].getDecimal())));
			_fe3d.textEntity_setFont(ID, string("game_assets\\fonts\\") + arguments[1].getString());
			_fe3d.textEntity_setTextContent(ID, arguments[2].getString());

			// In-engine viewport boundaries
			if (!_fe3d.application_isExported())
			{
				auto minPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition()));
				auto maxPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition() + _fe3d.misc_getViewportSize()));
				_fe3d.textEntity_setMinPosition(arguments[0].getString(), minPos);
				_fe3d.textEntity_setMaxPosition(arguments[0].getString(), maxPos);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:text_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
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
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
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
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				Vec2 change = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_move(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_move_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				Vec2 target = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				Vec2 speed = _convertGuiSizeToViewport(Vec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.textEntity_moveTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_rotate_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_rotateTo(arguments[0].getString(), arguments[1].getDecimal(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_scale_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				Vec2 target = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				Vec2 speed = _convertGuiSizeToViewport(Vec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.textEntity_scaleTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_rotation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
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
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
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
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				Vec2 change = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.textEntity_scale(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_color")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_content")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_setTextContent(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:text_set_alpha")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing text ID
			if (_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.textEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute text functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:text` functionality as a networking server!");
	}

	// Return
	return true;
}