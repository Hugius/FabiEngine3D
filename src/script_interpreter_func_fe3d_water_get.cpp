#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:water_get_dudv_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getDudvMapPath(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_displacement_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getDisplacementMapPath(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_normal_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getNormalMapPath(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:water_has_dudv_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_hasDudvMap(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_has_displacement_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_hasDisplacementMap(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_has_normal_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_hasNormalMap(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_max_depth")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getMaxDepth(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_ripple_speed_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getRippleSpeed(_fe3d->water_getSelectedId()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_ripple_speed_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getRippleSpeed(_fe3d->water_getSelectedId()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wave_speed_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWaveSpeed(_fe3d->water_getSelectedId()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wave_speed_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWaveSpeed(_fe3d->water_getSelectedId()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getHeight(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getColor(_fe3d->water_getSelectedId()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getColor(_fe3d->water_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getColor(_fe3d->water_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWireframeColor(_fe3d->water_getSelectedId()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWireframeColor(_fe3d->water_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wireframe_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWireframeColor(_fe3d->water_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_size")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getSize(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_texture_repeat")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getTextureRepeat(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_wave_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getWaveHeight(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_specular_shininess")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getSpecularShininess(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_specular_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_getSpecularIntensity(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_reflective")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_isReflective(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_refractive")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_isRefractive(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_specular")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_isSpecular(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_edged")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_isEdged(_fe3d->water_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:water_is_wireframed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dWater())
			{
				const auto result = _fe3d->water_isWireframed(_fe3d->water_getSelectedId());

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
		_throwRuntimeError("cannot access `fe3d:water` functionality as networking server!");
	}

	return true;
}