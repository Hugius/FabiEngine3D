#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:graphics_get_min_fog_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMinDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_max_fog_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMaxDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_thickness")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogThickness();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor().r;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor().g;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor().b;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_dof_dynamic")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_isDofDynamic();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_max_dof_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getMaxDofDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_blur_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDofBlurDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getShadowEyePosition().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getShadowEyePosition().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getShadowEyePosition().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_motion_blur_strength")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getMotionBlurStrength();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_map_path")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareMapPath();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_intensity")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareIntensity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_size")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareSensitivity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:graphics` functionality as networking server!");
	}

	return true;
}