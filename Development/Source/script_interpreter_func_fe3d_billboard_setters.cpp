#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dBillboardSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:billboard_place")
	{
		auto types = { SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("new billboard ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if billboard entity already exists
			if(_fe3d.billboardEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview billboard ID
			if(_validateFe3dBillboard("@" + arguments[1].getString(), true))
			{
				// Copy preview billboard
				_sceneEditor.copyPreviewBillboard(arguments[0].getString(), ("@" + arguments[1].getString()),
												  Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));

				// Stop animation if started
				if(_fe3d.billboardEntity_isSpriteAnimationStarted(arguments[0].getString()))
				{
					_fe3d.billboardEntity_stopSpriteAnimation(arguments[0].getString());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_delete")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_visible")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_position")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setPosition(arguments[0].getString(),
												  Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_rotation")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setRotation(arguments[0].getString(),
												  Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_size")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setSize(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_move(arguments[0].getString(),
										   Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_rotate(arguments[0].getString(),
											 Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_scale(arguments[0].getString(), Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_moveTo(arguments[0].getString(),
											 Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_rotateTo(arguments[0].getString(),
											   Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_scaleTo(arguments[0].getString(),
											  Vec2(arguments[1].getDecimal(), arguments[2].getDecimal()), arguments[3].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_color")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setColor(arguments[0].getString(),
											   Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_min_height")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_max_height")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_alpha")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_lightness")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_raycast_responsive")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::BILLBOARD_ENTITY);

				// Check if billboardEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_collision_responsive")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::BILLBOARD_ENTITY);

				// Check if billboardEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setCollisionResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_camera_facing_x")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setCameraFacingX(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_camera_facing_y")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_setCameraFacingY(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_start_animation")
	{
		auto types = { SVT::STRING, SVT::INTEGER };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_startSpriteAnimation(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_pause_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_pauseSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_resume_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_resumeSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_stop_animation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				_fe3d.billboardEntity_stopSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_text")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				// Check if billboard is not of type text
				if(!_fe3d.billboardEntity_isText(arguments[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" is not of type text!");
					return true;
				}
				else
				{
					_fe3d.billboardEntity_setTextContent(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute billboard functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:billboard` functionality as a networking server!");
	}

	// Return
	return true;
}