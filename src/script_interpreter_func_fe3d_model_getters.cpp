#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:model_is_existing")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.model_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:model_find_ids")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested model with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on sub ID
			for(const auto& ID : _fe3d.model_getAllIDs())
			{
				// If substring matches
				if(arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// @ sign is reserved
					if(ID[0] != '@')
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
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.model_getAllIDs();

			// Iterate through models
			for(const auto& ID : result)
			{
				// @ sign is reserved
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_visible")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_position_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBasePosition(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_position_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBasePosition(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_position_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBasePosition(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotation(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotation(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotation(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_origin_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotationOrigin(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_origin_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotationOrigin(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_origin_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseRotationOrigin(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_size_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_size_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_size_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getBaseSize(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_min_height")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_max_height")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _meshAnimationEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _meshAnimationEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _meshAnimationEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_animation_fading")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _meshAnimationEditor.isAnimationFading(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_animation_speed")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _meshAnimationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

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
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation autopause option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _meshAnimationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

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
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation frame index with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _meshAnimationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

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
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getLightness(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_r")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getColor(arguments[0].getString(), arguments[1].getString()).r;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_g")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getColor(arguments[0].getString(), arguments[1].getString()).g;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_color_b")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getColor(arguments[0].getString(), arguments[1].getString()).b;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_r")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getWireframeColor(arguments[0].getString(), arguments[1].getString()).r;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_g")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getWireframeColor(arguments[0].getString(), arguments[1].getString()).g;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_wireframe_color_b")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getWireframeColor(arguments[0].getString(), arguments[1].getString()).b;
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_transparency")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getTransparency(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getEmissionIntensity(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_texture_repeat")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getTextureRepeat(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_shininess")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getSpecularShininess(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getSpecularIntensity(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflectivity")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getReflectivity(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_distance")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailDistance(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_x")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_t")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_z")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_entity_id")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailEntityID(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_diffuse_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
					{
						auto result = _fe3d.model_getDiffuseMapPath(arguments[0].getString(), arguments[1].getString());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
					{
						auto result = _fe3d.model_getEmissionMapPath(arguments[0].getString(), arguments[1].getString());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
					{
						auto result = _fe3d.model_getSpecularMapPath(arguments[0].getString(), arguments[1].getString());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflection_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
					{
						auto result = _fe3d.model_getReflectionMapPath(arguments[0].getString(), arguments[1].getString());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_normal_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
					{
						auto result = _fe3d.model_getNormalMapPath(arguments[0].getString(), arguments[1].getString());
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
					}
				}
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