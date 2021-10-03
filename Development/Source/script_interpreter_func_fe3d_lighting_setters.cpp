#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dLightingSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:lighting_enable_ambient")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableAmbientLighting(
				_fe3d.gfx_getAmbientLightingColor(),
				_fe3d.gfx_getAmbientLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_ambient")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableAmbientLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_ambient_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getAmbientLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_ambient_intensity")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(_fe3d.gfx_getAmbientLightingColor(), arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_enable_directional")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				_fe3d.gfx_getDirectionalLightingColor(),
				_fe3d.gfx_getDirectionalLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_directional")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableDirectionalLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_position")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto position = Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
			_fe3d.gfx_enableDirectionalLighting(
				position,
				_fe3d.gfx_getDirectionalLightingColor(),
				_fe3d.gfx_getDirectionalLightingIntensity());
			_fe3d.billboardEntity_setPosition("@@lightSource", position);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getDirectionalLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_intensity")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				_fe3d.gfx_getDirectionalLightingColor(),
				arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_billboard_size")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(arguments[0].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_enable_spot")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_spot")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableSpotLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isSpotLightingEnabled();
			_fe3d.gfx_enableSpotLighting(
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableSpotLighting();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_intensity")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isSpotLightingEnabled();
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				arguments[0].getDecimal(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableSpotLighting();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_angle")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isSpotLightingEnabled();
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				arguments[0].getDecimal(),
				_fe3d.gfx_getSpotLightingDistance());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableSpotLighting();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_distance")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			bool wasEnabled = _fe3d.gfx_isSpotLightingEnabled();
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				arguments[0].getDecimal());
			if (!wasEnabled)
			{
				_fe3d.gfx_disableSpotLighting();
			}
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute lighting functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:lighting` functionality as a networking server!");
	}

	return true;
}