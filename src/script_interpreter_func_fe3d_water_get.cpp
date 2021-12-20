#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:water_get_dudv_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getDudvMapPath(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_displacement_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getDisplacementMapPath(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_normal_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getNormalMapPath(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_speed_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpeed(_fe3d.water_getSelectedID()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_speed_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpeed(_fe3d.water_getSelectedID()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_height")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getHeight(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getWireframeColor(_fe3d.water_getSelectedID()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getWireframeColor(_fe3d.water_getSelectedID()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getWireframeColor(_fe3d.water_getSelectedID()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_transparency")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getTransparency(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_size")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSize(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_texture_repeat")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getTextureRepeat(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wave_height")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getWaveHeight(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_specular_shininess")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpecularShininess(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_specular_intensity")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpecularIntensity(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_reflective")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_isReflective(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_refractive")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_isRefractive(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_specular")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_isSpecular(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_wireframed")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_isWireframed(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_quality")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getQuality(_fe3d.water_getSelectedID());
				if(result == WaterQuality::SKY)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "SKY"));
				}
				if(result == WaterQuality::SKY_TERRAIN)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "SKY_TERRAIN"));
				}
				if(result == WaterQuality::SKY_TERRAIN_MODELS)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "SKY_TERRAIN_MODELS"));
				}
				if(result == WaterQuality::SKY_TERRAIN_MODELS_BILLBOARDS)
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, "SKY_TERRAIN_MODELS_BILLBOARDS"));
				}
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
		_throwScriptError("cannot access `fe3d:water` functionality as networking server!");
	}

	// Return
	return true;
}