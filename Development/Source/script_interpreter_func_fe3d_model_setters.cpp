#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dModelSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:model_place")
	{
		auto types =
		{
			ScriptValueType::STRING, // New modelEntity ID
			ScriptValueType::STRING, // Preview modelEntity ID
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL // Position
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// New model ID cannot start with '@'
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("new model ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if modelEntity already exists
			if (_fe3d.modelEntity_isExisting(arguments[0].getString()))
			{
				_throwScriptError("model with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview model ID
			if (_validateFe3dModel("@" + arguments[1].getString(), true))
			{
				_sceneEditor.copyPreviewModel(arguments[0].getString(), ("@" + arguments[1].getString()),
					Vec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_visible")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setBasePosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setBaseRotation(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_rotation_origin")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setBaseRotationOrigin(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_size")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setBaseSize(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_moveBase(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_rotate")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_rotateBase(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_scale")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_scaleBase(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_move_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_moveBaseTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_rotate_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_rotateBaseTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_scale_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_scaleBaseTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_color")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				//_fe3d.modelEntity_setColor(arguments[0].getString(),
				//	Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				//returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_min_height")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_max_height")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_fe3d.modelEntity_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_lightness")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				//_fe3d.modelEntity_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_aabb_raycast_responsive")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::MODEL_ENTITY);

				// Check if modelEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for (const auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setRaycastResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_aabb_collision_responsive")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabbEntity_getChildIDs(arguments[0].getString(), AabbParentType::MODEL_ENTITY);

				// Check if modelEntity has no AABBs
				if (aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for (const auto& ID : aabbIDs)
				{
					_fe3d.aabbEntity_setCollisionResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_alpha")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				//_fe3d.modelEntity_setAlpha(arguments[0].getString(), arguments[1].getDecimal());
				//returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_start_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_animationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_pause_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_animationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_resume_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_animationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_fade_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_animationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_stop_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				_animationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_animation_speed")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					animationData->setSpeedMultiplier(arguments[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_set_animation_autopaused")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModel(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation autopaused option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					animationData->setAutoPaused(arguments[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute model functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:model` functionality as a networking server!");
	}

	// Return
	return true;
}