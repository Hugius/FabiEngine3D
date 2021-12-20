#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:terrain_get_pixel_height")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dTerrain())
			{
				float halfTerrainSize = (_fe3d.terrain_getSize(_fe3d.terrain_getSelectedID()) / 2.0f);
				auto result = _fe3d.terrain_getPixelHeight(_fe3d.terrain_getSelectedID(),
														   (arguments[0].getDecimal() + halfTerrainSize),
														   (arguments[1].getDecimal() + halfTerrainSize));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_height_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getHeightMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_diffuse_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getDiffuseMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_normal_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getNormalMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blend_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getBlendMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_diffuse_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getDiffuseMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_diffuse_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getDiffuseMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_diffuse_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getDiffuseMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_normal_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getNormalMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_normal_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getNormalMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_normal_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getNormalMapPath(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_height")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getMaxHeight(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_size")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getSize(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_lightness")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getLightness(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_shininess")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getSpecularShininess(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_specular_intensity")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getSpecularIntensity(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getWireframeColor(_fe3d.terrain_getSelectedID()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getWireframeColor(_fe3d.terrain_getSelectedID()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_wireframe_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getWireframeColor(_fe3d.terrain_getSelectedID()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_texture_repeat")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getTextureRepeat(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_red_repeat")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getRedRepeat(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_green_repeat")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getGreenRepeat(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_blue_repeat")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getBlueRepeat(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_is_specular")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_isSpecular(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_is_wireframed")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_isWireframed(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as networking server!");
	}

	// Return
	return true;
}