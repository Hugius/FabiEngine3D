#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:graphics_set_ambient_lighting_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setAmbientLightingEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_ambient_lighting_color")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setAmbientLightingColor(fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_ambient_lighting_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setAmbientLightingIntensity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_directional_lighting_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDirectionalLightingEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_directional_lighting_color")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDirectionalLightingColor(fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_directional_lighting_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDirectionalLightingIntensity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_planar_reflection_height")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setPlanarReflectionHeight(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_planar_reflection_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setPlanarReflectionQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_planar_refraction_height")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setPlanarRefractionHeight(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_planar_refraction_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setPlanarRefractionQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadows_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowsEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));

		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_position")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowPositionOffset(fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_lookat")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowLookatOffset(fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_size")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowSize(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_lightness")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowLightness(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_bias")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowBias(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_interval")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowInterval(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_pcf_count")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowPcfCount(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_following_camera_x")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowFollowingCameraX(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_following_camera_y")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowFollowingCameraY(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_shadow_following_camera_z")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setShadowFollowingCameraZ(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setFogEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_color")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setFogColor(fvec3(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal()));

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_thickness")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setFogThickness(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_min_fog_distance")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setFogMinDistance(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_max_fog_distance")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setFogMaxDistance(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDofEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic_distance")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDofDynamicDistance(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_blur_distance")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDofBlurDistance(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDofDynamic(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setDofQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setMotionBlurEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setMotionBlurIntensity(args[0]->getDecimal());
			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setMotionBlurQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setLensFlareEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!Tools::isApplicationExported() && _currentProjectId.empty())
			{
				abort();
			}

			const auto isExported = Tools::isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = (rootPath + (isExported ? "" : ("projects\\" + _currentProjectId + "\\")) + "assets\\image\\miscellaneous\\flare_map\\");
			const auto filePath = (targetDirectoryPath + args[0]->getString());

			_fe3d->graphics_setLensFlareMap(filePath);

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setLensFlareIntensity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_sensitivity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setLensFlareSensitivity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setBloomIntensity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setBloomQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_blur_count")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setBloomBlurCount(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_type")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(args[0]->getString() == "EVERYTHING")
			{
				_fe3d->graphics_setBloomType(BloomType::EVERYTHING);

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
			else if(args[0]->getString() == "PARTS")
			{
				_fe3d->graphics_setBloomType(BloomType::PARTS);

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
			else
			{
				_throwRuntimeError("bloom type is invalid");

				return true;
			}
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setBloomEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_speed")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setSkyExposureSpeed(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_intensity")
	{
		const auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setSkyExposureIntensity(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setSkyExposureEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_anti_aliasing_enabled")
	{
		const auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setAntiAliasingEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_anisotropic_filtering_quality")
	{
		const auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->graphics_setAnisotropicFilteringQuality(args[0]->getInteger());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
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