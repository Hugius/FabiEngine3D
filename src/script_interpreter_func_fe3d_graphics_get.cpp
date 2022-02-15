#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:graphics_is_ambient_lighting_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isAmbientLightingEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_ambient_lighting_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().r;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_ambient_lighting_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().g;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_ambient_lighting_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingColor().b;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_ambient_lighting_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getAmbientLightingIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_directional_lighting_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isDirectionalLightingEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingPosition().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().r;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().g;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingColor().b;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_directional_lighting_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDirectionalLightingIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_cube_reflection_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getCubeReflectionQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_planar_reflection_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getPlanarReflectionQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_planar_refraction_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getPlanarRefractionQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_planar_reflection_height")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getPlanarReflectionHeight());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowPositionOffset().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowPositionOffset().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowPositionOffset().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_lookat_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowLookatOffset().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_lookat_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowLookatOffset().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_lookat_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowLookatOffset().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_size")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowSize();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_lightness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getShadowLightness();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getShadowQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_shadow_interval")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getShadowInterval());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_shadow_following_camera")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isShadowFollowingCamera();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_fog_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isFogEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_min_fog_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogMinDistance();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_max_fog_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogMaxDistance();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_thickness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogThickness();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogColor().r;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogColor().g;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getFogColor().b;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getDofQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_dof_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isDofEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_dof_dynamic")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isDofDynamic();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_dynamic_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDofDynamicDistance();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_blur_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getDofBlurDistance();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_motion_blur_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getMotionBlurIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_motion_blur_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getMotionBlurQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_motion_blur_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isMotionBlurEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_lens_flare_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isLensFlareEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getLensFlareMapPath();

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:graphics_has_lens_flare_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_hasLensFlareMap();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getLensFlareIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_sensitivity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getLensFlareSensitivity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getBloomIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getBloomQuality());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_blur_count")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = static_cast<int>(_fe3d->gfx_getBloomBlurCount());

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_bloom_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isBloomEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_type")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto bloomType = _fe3d->gfx_getBloomType();

			if(bloomType == BloomType::EVERYTHING)
			{
				const auto result = "EVERYTHING";

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
			if(bloomType == BloomType::PARTS)
			{
				const auto result = "PARTS";

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:graphics_is_sky_exposure_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_isSkyExposureEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_sky_exposure_speed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getSkyExposureSpeed();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_sky_exposure_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->gfx_getSkyExposureIntensity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:graphics` functionality as a networking server");
		return true;
	}

	return true;
}