#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dImageEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("requested image ID cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.imageEntity_isExisting(ID))
	{
		_throwScriptError("requested image with ID \"" + ID + "\" does not exist!");

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dImageEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:image_is_existing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("requested image ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.imageEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:image_find_ids")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("requested image ID cannot start with '@'");
				return true;
			}

			// Find full imageEntity IDs based on part ID
			for (auto& ID : _fe3d.imageEntity_getAllIDs())
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
	else if (functionName == "fe3d:image_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.imageEntity_getAllIDs();

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
	else if (functionName == "fe3d:image_place")
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
				_throwScriptError("new image ID cannot start with '@'");
				return true;
			}

			// Check if imageEntity already exists
			if (_fe3d.imageEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("image with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}
			
			// Add image
			_fe3d.imageEntity_add(
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
				_fe3d.imageEntity_setMinPosition(arguments[0].getString(), minPos);
				_fe3d.imageEntity_setMaxPosition(arguments[0].getString(), maxPos);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:image_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_visible")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				// Determine if image must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.imageEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.imageEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_is_visible")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				Vec2 position = _convertGuiPositionToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_move(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_position_x")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:image_get_position_y")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiPositionFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:image_set_rotation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_rotation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				Vec2 size = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				Vec2 factor = _convertGuiSizeToViewport(Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.imageEntity_scale(arguments[0].getString(), factor);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_width")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).x));
			}
		}
	}
	else if (functionName == "fe3d:image_get_height")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, _convertGuiSizeFromViewport(result).y));
			}
		}
	}
	else if (functionName == "fe3d:image_set_color")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_color")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_alpha")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_get_alpha")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_getAlpha(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:image_start_animation")
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
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setAnimationRows(arguments[0].getString(), arguments[1].getInteger());
				_fe3d.imageEntity_setAnimationColumns(arguments[0].getString(), arguments[2].getInteger());
				_fe3d.imageEntity_setAnimationFramestep(arguments[0].getString(), arguments[3].getInteger());
				_fe3d.imageEntity_startAnimation(arguments[0].getString(), arguments[4].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_pause_animation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_pauseAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_resume_animation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_resumeAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_stop_animation")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_stopAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_is_animation_started")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isAnimationStarted(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_is_animation_playing")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_is_animation_paused")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isAnimationPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_horizontally")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setMirroredHorizontally(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_vertically")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				_fe3d.imageEntity_setMirroredVertically(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_is_mirrored_horizontally")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isMirroredHorizontally(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:image_is_mirrored_vertically")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing image ID
			if (_validateFe3dImageEntity(arguments[0].getString()))
			{
				auto result = _fe3d.imageEntity_isMirroredVertically(arguments[0].getString());
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