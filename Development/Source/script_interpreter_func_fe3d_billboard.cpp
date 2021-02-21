#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dBillboardEntity(const string& ID, bool previewEntity)
{
	// Cannot request/delete a preview entity
	if (!previewEntity && ID.front() == '@')
	{
		_throwScriptError("Requested billboard ID cannot start with '@'");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.billboardEntity_isExisting(ID))
	{
		if (previewEntity)
		{
			_throwScriptError("Requested billboard with ID \"" + ID.substr(1) + "\" does not exist!");
		}
		else
		{
			_throwScriptError("Requested billboard with ID \"" + ID + "\" does not exist!");
		}

		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dBillboardEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:billboard_is_existing") // Get billboardEntity existence
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("Requested billboard ID cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.billboardEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:billboard_get_all_ids") // Get all billboardEntity IDs
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.billboardEntity_getAllIDs();

			// For every billboard
			for (auto& ID : result)
			{
				// Only non-preview billboards
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:billboard_place") // Create billboardEntity
	{
		auto types =
		{
			ScriptValueType::STRING, // New billboardEntity ID
			ScriptValueType::STRING, // Preview billboardEntity ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Position
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// New billboard ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("New billboard ID cannot start with '@'");
				return true;
			}

			// Check if billboard entity already exists
			if (_fe3d.billboardEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("Billboard with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview billboard ID
			if (_validateFe3dBillboardEntity("@" + arguments[1].getString(), true))
			{
				_sceneEditor.placeBillboard(arguments[0].getString(), "@" + arguments[1].getString(),
					Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				_fe3d.billboardEntity_stopSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_delete") // Delete billboardEntity
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_visible") // Set billboardEntity visibility
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				// Determine if billboard must be visible or not
				if (arguments[1].getBoolean())
				{
					_fe3d.billboardEntity_show(arguments[0].getString());
				}
				else
				{
					_fe3d.billboardEntity_hide(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_is_visible") // Get billboardEntity visibility
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_position") // Set billboardEntity position
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setPosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_move") // Move billboardEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_move(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_position") // Get billboardEntity position
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_rotation") // Set billboardEntity rotation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setRotation(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_rotate") // Rotate billboardEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_rotate(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_rotation") // Get billboardEntity rotation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_size") // Set billboardEntity size
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setSize(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_scale") // Scale billboardEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_scale(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_width") // Get billboardEntity width
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_height") // Get billboardEntity height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_color") // Set billboardEntity color
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setColor(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_color") // Get billboardEntity color
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_min_height") // Set billboardEntity minimum height
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_min_height") // Get billboardEntity minimum height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_max_height") // Set billboardEntity maximum height
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_max_height") // Get billboardEntity maximum height
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_lightness") // Set billboardEntity lightness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_lightness") // Get billboardEntity lightness
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getLightness(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_aabb_responsive") // Set billboardEntity AABB responsiveness
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), false, true);

				// Check if billboardEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("Billboard has no bound AABBs!");
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
	else if (functionName == "fe3d:billboard_set_camera_facing_x") // Set billboardEntity camera facing X
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setCameraFacingX(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_is_facing_camera_x") // Check if billboardEntity is facing camera X
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isFacingCameraX(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_camera_facing_y") // Set billboardEntity camera facing Y
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setCameraFacingY(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_is_facing_camera_y") // Check if billboardEntity is facing camera Y
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isFacingCameraY(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_start_animation") // Play billboardEntity animation
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_playSpriteAnimation(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_is_animation_playing") // Check if billboardEntity animation is playing
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_stop_animation") // Stop billboardEntity animation
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				_fe3d.billboardEntity_stopSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:billboard_is_animation_finished") // Check if billboardEntity animation is finished
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isAnimationFinished(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:billboard_set_text") // Set billboardEntity text
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				// Check if billboard is of type text
				if (_fe3d.billboardEntity_getFontPath(arguments[0].getString()).empty())
				{
					_throwScriptError("Billboard is not of type text!");
					return true;
				}
				else
				{
					_fe3d.billboardEntity_setTextContent(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
				}
			}
		}
	}
	else if (functionName == "fe3d:billboard_get_text") // Get billboardEntity text
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate existing billboard ID
			if (_validateFe3dBillboardEntity(arguments[0].getString()))
			{
				// Check if billboard is of type text
				if (_fe3d.billboardEntity_getFontPath(arguments[0].getString()).empty())
				{
					_throwScriptError("Billboard is not of type text!");
					return true;
				}
				else
				{
					auto result = _fe3d.billboardEntity_getTextContent(arguments[0].getString());
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
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