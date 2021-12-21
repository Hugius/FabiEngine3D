#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dGraphicsSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:graphics_enable_fog")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableFog();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_fog")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableFog(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setFogColor(fvec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_fog_thickness")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setFogThickness(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_min_fog_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setFogMinDistance(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_max_fog_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setFogMaxDistance(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_dof")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableDOF();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_dof")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableDOF(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDofDynamicDistance(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_blur_distance")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDofBlurDistance(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDofDynamic(arguments[0].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_dof_dynamic")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDofQuality(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_motion_blur")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableMotionBlur();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_motion_blur")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableMotionBlur(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_strength")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setMotionBlurStrength(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_motion_blur_quality")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setMotionBlurQuality(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_lens_flare")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableLensFlare();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_lens_flare")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableLensFlare(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate project ID
			if(_currentProjectID.empty())
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dGraphicsSetter");
			}

			// Compose file path
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\texture\\flare_map\\");
			const string filePath = (targetDirectoryPath + arguments[0].getString());

			// Set flare map
			_fe3d.gfx_setLensFlareMap(filePath);

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setLensFlareIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_lens_flare_sensitivity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setLensFlareSensitivity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setBloomIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_quality")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setBloomQuality(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_blur_count")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setBloomBlurCount(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_bloom_type")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(arguments[0].getString() == "EVERYTHING")
			{
				_fe3d.gfx_setBloomType(BloomType::EVERYTHING);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else if(arguments[0].getString() == "PARTS")
			{
				_fe3d.gfx_setBloomType(BloomType::PARTS);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
			else
			{
				Logger::throwWarning("invalid bloom type!");
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:graphics_set_enable_bloom")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableBloom();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_disable_bloom")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableBloom(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_speed")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setSkyExposureSpeed(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_set_sky_exposure_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setSkyExposureIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_enable_sky_exposure")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableSkyExposure();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:graphics_disable_sky_exposure")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableSkyExposure(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
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