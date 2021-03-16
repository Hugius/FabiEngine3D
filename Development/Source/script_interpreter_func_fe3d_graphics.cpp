#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dGraphicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:graphics_enable_fog")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(),
				_fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_fog")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableFog();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_min_fog_distance")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(arguments[0].getDecimal(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_min_fog_distance")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMinDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_max_fog_distance")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_max_fog_distance")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMaxDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_thickness")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_thickness")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogThickness();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_color")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_enable_dof")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), _fe3d.gfx_getaMaxDofDistance(), _fe3d.gfx_getDofBlurDistance());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_dof")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableDOF();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = { ScriptValueType::BOOLEAN };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(arguments[0].getBoolean(), _fe3d.gfx_getaMaxDofDistance(), _fe3d.gfx_getDofBlurDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_is_dof_dynamic")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_isDofDynamic();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_max_dof_distance")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), arguments[0].getDecimal(), _fe3d.gfx_getDofBlurDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_max_dof_distance")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getaMaxDofDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_dof_blur_distance")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), _fe3d.gfx_getaMaxDofDistance(), arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_dof_blur_distance")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDofBlurDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_shadow_position")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableShadows(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getShadowCenter(), _fe3d.gfx_getShadowSize(), _fe3d.gfx_getShadowReach(),
				_fe3d.gfx_getShadowLightness(), _fe3d.gfx_isShadowFollowingCamera(), _fe3d.gfx_isSoftShadowingEnabled());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_shadow_position")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getShadowEyePosition();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_enable_light_mapping")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableLightMapping();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_light_mapping")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableLightMapping();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_sky_hdr")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableSkyHDR(_fe3d.gfx_getSkyHdrBrightnessFactor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_sky_hdr")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableSkyHDR();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_sky_hdr_brightness")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isSkyHdrEnabled();
			_fe3d.gfx_enableSkyHDR(arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableSkyHDR();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_sky_hdr_brightness")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSkyHdrBrightnessFactor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_enable_motion_blur")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableMotionBlur(_fe3d.gfx_getMotionBlurStrength());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_motion_blur")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableMotionBlur();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_motion_blur_strength")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isMotionBlurEnabled();
			_fe3d.gfx_enableMotionBlur(arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableMotionBlur();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_motion_blur_strength")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getMotionBlurStrength();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_enable_lens_flare")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), _fe3d.gfx_getLensFlareIntensity(), _fe3d.gfx_getLensFlareMultiplier());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_lens_flare")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableLensFlare();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_map")
	{
		auto types = { ScriptValueType::STRING };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			_fe3d.gfx_enableLensFlare(arguments[0].getString(), _fe3d.gfx_getLensFlareIntensity(), _fe3d.gfx_getLensFlareMultiplier());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_lens_flare_map_path")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareMapPath();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_intensity")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), arguments[0].getDecimal(), _fe3d.gfx_getLensFlareMultiplier());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_lens_flare_intensity")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_multiplier")
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), _fe3d.gfx_getLensFlareIntensity(), arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_lens_flare_multiplier")
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getLensFlareMultiplier();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}