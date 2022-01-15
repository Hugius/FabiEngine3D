#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dLightingGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:lighting_is_ambient_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isAmbientLightingEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_ambient_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().r;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_ambient_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().g;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_ambient_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().b;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_ambient_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingIntensity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_is_directional_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isDirectionalLightingEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().x;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().y;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().z;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().r;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().g;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().b;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingIntensity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_cube_reflection_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getCubeReflectionQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_get_planar_reflection_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getPlanarReflectionQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_get_planar_refraction_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getPlanarRefractionQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_get_planar_reflection_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getPlanarReflectionHeight();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_eye_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowEyePosition().x;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_eye_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowEyePosition().y;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_eye_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowEyePosition().z;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_center_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowCenterPosition().x;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_center_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowCenterPosition().y;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_center_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowCenterPosition().z;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_size")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowSize();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_lightness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowLightness();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_get_shadow_interval")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowInterval();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:lighting_is_shadow_following_camera")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isShadowFollowingCamera();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:lighting` functionality as networking server!");
	}

	return true;
}