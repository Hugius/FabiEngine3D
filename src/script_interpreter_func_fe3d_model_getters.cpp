#include "script_interpreter.hpp"

using SVT = ScriptValueType;

static const vector<string> extractModelPartIDs(FabiEngine3D& fe3d, const string& modelID, const string& partID)
{
	if(partID.empty())
	{
		return fe3d.modelEntity_getPartIDs(modelID);
	}
	else
	{
		return { partID };
	}
}

const bool ScriptInterpreter::_executeFe3dModelGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:model_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.modelEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:model_find_ids")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on part ID
			for(const auto& ID : _fe3d.modelEntity_getAllIDs())
			{
				// If substring matches
				if(arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// @ sign is reserved
					if(ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_all_ids")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.modelEntity_getAllIDs();

			// For every model
			for(const auto& ID : result)
			{
				// @ sign is reserved
				if(ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_visible")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_position")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getBasePosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getBaseRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_origin")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getBaseRotationOrigin(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_size")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getBaseSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_max_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.modelEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_started")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animationEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_playing")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animationEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_paused")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animationEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_fading")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _animationEditor.isAnimationFading(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_speed")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->getSpeedMultiplier();
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_autopaused")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation autopause option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->isAutoPaused();
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_frame_index")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation frame index with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if(animationData != nullptr)
				{
					auto result = animationData->getFrameIndex();
					returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_lightness")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Calculate average
				vector<float> total;
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					total.push_back(_fe3d.modelEntity_getLightness(arguments[0].getString(), partID));
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, Math::calculateAverage(total)));
			}
		}
	}
	else if(functionName == "fe3d:model_get_color")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Calculate average
				vector<Vec3> total;
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					total.push_back(_fe3d.modelEntity_getColor(arguments[0].getString(), partID));
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, Math::calculateAverage(total)));
			}
		}
	}
	else if(functionName == "fe3d:model_get_transparency")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Calculate average
				vector<float> total;
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					total.push_back(_fe3d.modelEntity_getTransparency(arguments[0].getString(), partID));
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, Math::calculateAverage(total)));
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_intensity")
	{
		auto types = { SVT::STRING, SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Calculate average
				vector<float> total;
				for(const auto& partID : extractModelPartIDs(_fe3d, arguments[0].getString(), arguments[1].getString()))
				{
					total.push_back(_fe3d.modelEntity_getEmissionIntensity(arguments[0].getString(), partID));
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, Math::calculateAverage(total)));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute model functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:model` functionality as a networking server!");
	}

	// Return
	return true;
}