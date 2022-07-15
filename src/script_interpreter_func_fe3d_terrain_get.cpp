#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:terrain_get_selected_id")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->terrain_getSelectedId();

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:terrain_get_editor_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _duplicator->getEditorTerrainId(args[0]->getString()).substr(1);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->terrain_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:terrain_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->terrain_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_min_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMinClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_min_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMinClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_min_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMinClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMaxClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMaxClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMaxClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_pixel_height")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto halfTerrainSize = (_fe3d->terrain_getSize(_fe3d->terrain_getSelectedId()) * 0.5f);
				const auto result = _fe3d->terrain_getPixelHeight(_fe3d->terrain_getSelectedId(), (args[1]->getDecimal() + halfTerrainSize), (args[2]->getDecimal() + halfTerrainSize));

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_height_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getHeightMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_normal_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blend_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getBlendMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_normal_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_normal_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_normal_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_normal_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blend_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasBlendMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_red_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_green_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blue_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_red_normal_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_green_normal_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blue_normal_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_height")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getMaxHeight(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_size")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getSize(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_lightness")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getLightness(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_shininess")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getSpecularShininess(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_intensity")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getSpecularIntensity(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedId()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getColor(_fe3d->terrain_getSelectedId()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getColor(_fe3d->terrain_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getColor(_fe3d->terrain_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_texture_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getTextureRepeat(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getRedTextureRepeat(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getGreenTextureRepeat(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_getBlueTextureRepeat(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_is_specular")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_isSpecular(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_is_wireframed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_isWireframed(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_is_shadowed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				const auto result = _fe3d->terrain_isShadowed(_fe3d->terrain_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:terrain` functionality as a networking server");

		return true;
	}

	return true;
}