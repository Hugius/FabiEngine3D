#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dImageSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:image_place")
	{
		auto types =
		{
			SVT::STRING, // ID
			SVT::STRING, // Texture path
			SVT::DECIMAL, SVT::DECIMAL, // Position
			SVT::DECIMAL, // Rotation
			SVT::DECIMAL, SVT::DECIMAL // Size
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			auto ID = arguments[0].getString();

			// New image ID cannot start with '@'
			if (ID.front() == '@')
			{
				_throwScriptError("new image ID (\"" + ID + "\") cannot start with '@'");
				return true;
			}

			// Check if imageEntity already exists
			if (_fe3d.imageEntity_isExisting(ID))
			{
				_throwScriptError("image with ID \"" + ID + "\" already exists!");
				return true;
			}
			
			// Create image
			_fe3d.imageEntity_create(ID, true);
			_fe3d.imageEntity_setPosition(ID, _convertGuiPositionToViewport(Vec2(arguments[2].getDecimal(), arguments[3].getDecimal())));
			_fe3d.imageEntity_setRotation(ID, arguments[4].getDecimal());
			_fe3d.imageEntity_setSize(ID, _convertGuiSizeToViewport(Vec2(arguments[5].getDecimal(), arguments[6].getDecimal())));
			_fe3d.imageEntity_setDiffuseMap(ID, string(("game_assets\\textures\\image_maps\\") + arguments[1].getString()));

			// In-engine viewport boundaries
			if (!_fe3d.application_isExported())
			{
				auto minPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition()));
				auto maxPos = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getViewportPosition() + _fe3d.misc_getViewportSize()));
				_fe3d.imageEntity_setMinPosition(ID, minPos);
				_fe3d.imageEntity_setMaxPosition(ID, maxPos);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:image_delete")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_visible")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_position")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 position = _convertGuiPositionToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 change = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_move(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 target = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				Vec2 speed = _convertGuiSizeToViewport(Vec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.imageEntity_moveTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_rotation")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_rotateTo(arguments[0].getString(), arguments[1].getDecimal(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_size")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 size = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 change = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_scale(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				Vec2 target = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				Vec2 speed = _convertGuiSizeToViewport(Vec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.imageEntity_scaleTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_color")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_alpha")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_start_animation")
	{
		auto types =
		{
			SVT::STRING,
			SVT::INTEGER,
			SVT::INTEGER,
			SVT::INTEGER,
			SVT::INTEGER
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setSpriteAnimationRows(arguments[0].getString(), arguments[1].getInteger());
				_fe3d.imageEntity_setSpriteAnimationColumns(arguments[0].getString(), arguments[2].getInteger());
				_fe3d.imageEntity_setSpriteAnimationFramestep(arguments[0].getString(), arguments[3].getInteger());
				_fe3d.imageEntity_startSpriteAnimation(arguments[0].getString(), arguments[4].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_pause_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_pauseSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_resume_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_resumeSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_stop_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_stopSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_horizontally")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setMirroredHorizontally(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_vertically")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.imageEntity_setMirroredVertically(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute image functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:image` functionality as a networking server!");
	}

	// Return
	return true;
}