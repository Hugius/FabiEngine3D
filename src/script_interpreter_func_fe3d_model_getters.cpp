#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:model_is_existing")
	{
		auto types = {SVT::STRING};

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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lightness")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
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
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailDistance(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_t")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_size_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailSize(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_lod_entity_id")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getLevelOfDetailEntityID(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_mesh_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getMeshPath(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:model_get_diffuse_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getDiffuseMapPath(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_emission_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getEmissionMapPath(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_specular_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getSpecularMapPath(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_reflection_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getReflectionMapPath(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_normal_map_path")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_getNormalMapPath(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_shadowed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isShadowed(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_frozen")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isFrozen(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_reflected")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isReflected(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_bright")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isBright(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_face_culled")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isFaceCulled(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_reflective")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_isReflective(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_specular")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_isSpecular(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_is_instanced")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_isInstanced(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:model_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				if(_validateFe3dModelPart(arguments[0].getString(), arguments[1].getString()))
				{
					auto result = _fe3d.model_isWireframed(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_get_rotation_order")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dModel(arguments[0].getString(), false))
			{
				auto result = _fe3d.model_getRotationOrder(arguments[0].getString());
				if(result == DirectionOrder::XYZ)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "XYZ"));
				}
				if(result == DirectionOrder::XZY)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "XZY"));
				}
				if(result == DirectionOrder::YXZ)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "YXZ"));
				}
				if(result == DirectionOrder::YZX)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "YZX"));
				}
				if(result == DirectionOrder::ZXY)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "ZXY"));
				}
				if(result == DirectionOrder::ZYX)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "ZYX"));
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