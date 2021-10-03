#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dGraphicsSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:graphics_enable_fog")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(),
				_fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_fog")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableFog();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_min_fog_distance")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(arguments[0].getDecimal(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_max_fog_distance")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_thickness")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogColor());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isFogEnabled();
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			if (!wasEnabled)
			{
				_fe3d.gfx_disableFog();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_dof")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), _fe3d.gfx_getaMaxDofDistance(), _fe3d.gfx_getDofBlurDistance());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_dof")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableDOF();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = { SVT::BOOLEAN };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(arguments[0].getBoolean(), _fe3d.gfx_getaMaxDofDistance(), _fe3d.gfx_getDofBlurDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_max_dof_distance")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), arguments[0].getDecimal(), _fe3d.gfx_getDofBlurDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_dof_blur_distance")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isDofEnabled();
			_fe3d.gfx_enableDOF(_fe3d.gfx_isDofDynamic(), _fe3d.gfx_getaMaxDofDistance(), arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableDOF();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_shadows")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableShadows(
				_fe3d.gfx_getShadowEye(),
				_fe3d.gfx_getShadowCenter(),
				_fe3d.gfx_getShadowSize(),
				_fe3d.gfx_getShadowReach(),
				_fe3d.gfx_getShadowLightness(),
				_fe3d.gfx_isShadowFollowingCamera(),
				_fe3d.gfx_getShadowInterval());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_shadows")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableShadows();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_shadow_position")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableShadows(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getShadowCenter(),
				_fe3d.gfx_getShadowSize(),
				_fe3d.gfx_getShadowReach(),
				_fe3d.gfx_getShadowLightness(),
				_fe3d.gfx_isShadowFollowingCamera(),
				_fe3d.gfx_getShadowInterval());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_motion_blur")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableMotionBlur(_fe3d.gfx_getMotionBlurStrength());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_motion_blur")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableMotionBlur();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_motion_blur_strength")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isMotionBlurEnabled();
			_fe3d.gfx_enableMotionBlur(arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableMotionBlur();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_lens_flare")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), _fe3d.gfx_getLensFlareIntensity(), _fe3d.gfx_getLensFlareMultiplier());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_lens_flare")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableLensFlare();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_map")
	{
		auto types = { SVT::STRING };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			const string targetDirectory = string("game_assets\\textures\\flare_maps\\");
			const string filePath = targetDirectory + arguments[0].getString();
			_fe3d.gfx_enableLensFlare(filePath, _fe3d.gfx_getLensFlareIntensity(), _fe3d.gfx_getLensFlareMultiplier());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_intensity")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), arguments[0].getDecimal(), _fe3d.gfx_getLensFlareMultiplier());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_lens_flare_multiplier")
	{
		auto types = { SVT::DECIMAL };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isLensFlareEnabled();
			_fe3d.gfx_enableLensFlare(_fe3d.gfx_getLensFlareMapPath(), _fe3d.gfx_getLensFlareIntensity(), arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableLensFlare();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute graphics functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:graphics` functionality as a networking server!");
	}

	return true;
}