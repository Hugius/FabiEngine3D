#include "script_interpreter.hpp"

using SVT = ScriptValueType;

static const vector<string> extractModelPartIDs(FabiEngine3D& fe3d, const string& modelID, const string& partID)
{
	if(partID.empty())
	{
		return fe3d.model_getPartIDs(modelID);
	}
	else
	{
		return {partID};
	}
}

const bool ScriptInterpreter::_executeFe3dModelSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:model_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("new model ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if modelEntity already exists
			if(_fe3d.model_isExisting(arguments[0].getString()))
			{
				_throwScriptError("model with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate preview model ID
			if(_validateFe3dModel("@" + arguments[1].getString(), true))
			{
				_worldEditor.copyPreviewModel(arguments[0].getString(), ("@" + arguments[1].getString()),
											  fvec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setBasePosition(arguments[0].getString(),
												  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setBaseRotation(arguments[0].getString(),
												  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation_origin")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setBaseRotationOrigin(arguments[0].getString(),
														fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setBaseSize(arguments[0].getString(),
											  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_moveBase(arguments[0].getString(),
										   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_rotateBase(arguments[0].getString(),
											 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_scaleBase(arguments[0].getString(),
											fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_moveBaseTo(arguments[0].getString(),
											 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_rotateBaseTo(arguments[0].getString(),
											   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_scaleBaseTo(arguments[0].getString(),
											  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_min_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_fe3d.model_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabb_getChildIDs(arguments[0].getString(), AabbParentEntityType::MODEL);

				// Check if modelEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabb_setRaycastResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabb_getChildIDs(arguments[0].getString(), AabbParentEntityType::MODEL);

				// Check if modelEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabb_setCollisionResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_start_animation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_pause_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_resume_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_fade_animation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_stop_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				_animationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_speed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					animationData->setSpeedMultiplier(arguments[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_autopaused")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation autopaused option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					animationData->setAutoPaused(arguments[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_color")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Set color
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					_fe3d.model_setColor(arguments[0].getString(), partID,
											   fvec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_lightness")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Set lightness
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					_fe3d.model_setLightness(arguments[0].getString(), partID, arguments[2].getDecimal());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_transparency")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Set transparency
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					_fe3d.model_setTransparency(arguments[0].getString(), partID, arguments[2].getDecimal());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Set emission intensity
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					_fe3d.model_setEmissionIntensity(arguments[0].getString(), partID, arguments[2].getDecimal());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute model functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:model` functionality as networking server!");
	}

	// Return
	return true;
}