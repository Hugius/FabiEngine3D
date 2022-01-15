#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:terrain_get_pixel_height")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				float halfTerrainSize = (_fe3d->terrain_getSize(_fe3d->terrain_getSelectedID()) / 2.0f);
				const auto result = _fe3d->terrain_getPixelHeight(_fe3d->terrain_getSelectedID(), (args[0].getDecimal() + halfTerrainSize), (args[1].getDecimal() + halfTerrainSize));
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_height_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getHeightMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_diffuse_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_normal_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blend_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getBlendMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_diffuse_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_diffuse_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_diffuse_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getDiffuseMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_normal_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_normal_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_normal_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getNormalMapPath(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_diffuse_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_normal_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blend_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasBlendMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_red_diffuse_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_green_diffuse_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blue_diffuse_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasDiffuseMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_red_normal_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_green_normal_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_has_blue_normal_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_hasNormalMap(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}

	else if(functionName == "fe3d:terrain_get_max_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getMaxHeight(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_size")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getSize(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_lightness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getLightness(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_shininess")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getSpecularShininess(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getSpecularIntensity(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedID()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedID()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getWireframeColor(_fe3d->terrain_getSelectedID()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_texture_repeat")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getTextureRepeat(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_repeat")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getRedTextureRepeat(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_repeat")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getGreenTextureRepeat(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_repeat")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_getBlueTextureRepeat(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_is_specular")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_isSpecular(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_is_wireframed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->terrain_isWireframed(_fe3d->terrain_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as networking server!");
	}

	return true;
}