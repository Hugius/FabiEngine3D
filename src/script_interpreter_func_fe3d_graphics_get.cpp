#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:graphics_is_fog_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isFogEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_min_fog_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogMinDistance();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_max_fog_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogMaxDistance();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_thickness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogThickness();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogColor().r;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogColor().g;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_fog_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getFogColor().b;
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getDofQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:graphics_is_dof_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isDofEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_dof_dynamic")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isDofDynamic();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_dynamic_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getDofDynamicDistance();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_dof_blur_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getDofBlurDistance();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_motion_blur_strength")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getMotionBlurStrength();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_motion_blur_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getMotionBlurQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:graphics_is_motion_blur_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isMotionBlurEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_is_lens_flare_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isLensFlareEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getLensFlareMapPath();
			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getLensFlareIntensity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_lens_flare_sensitivity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getLensFlareSensitivity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getBloomIntensity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_quality")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getBloomQuality();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_blur_count")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getBloomBlurCount();
			returnValues.push_back(ScriptValue(SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:graphics_is_bloom_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isBloomEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_bloom_type")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getBloomType();
			if(result == BloomType::EVERYTHING)
			{
				returnValues.push_back(ScriptValue(SVT::STRING, "EVERYTHING"));
			}
			if(result == BloomType::PARTS)
			{
				returnValues.push_back(ScriptValue(SVT::STRING, "PARTS"));
			}
		}
	}
	else if(functionName == "fe3d:graphics_is_sky_exposure_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_isSkyExposureEnabled();
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_sky_exposure_speed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getSkyExposureSpeed();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:graphics_get_sky_exposure_intensity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->gfx_getSkyExposureIntensity();
			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:graphics` functionality as networking server!");
	}

	return true;
}