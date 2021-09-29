#include "script_interpreter.hpp"

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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_ambient")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableAmbientLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_ambient_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getAmbientLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_ambient_color")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_ambient_intensity")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(_fe3d.gfx_getAmbientLightingColor(), arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_ambient_intensity")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_directional")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableDirectionalLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_position")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto position = Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
			_fe3d.gfx_enableDirectionalLighting(
				position,
				_fe3d.gfx_getDirectionalLightingColor(),
				_fe3d.gfx_getDirectionalLightingIntensity());
			_fe3d.billboardEntity_setPosition("@@lightSource", position);
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_directional_position")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingPosition();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getDirectionalLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_directional_color")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_intensity")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				_fe3d.gfx_getDirectionalLightingColor(),
				arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_directional_intensity")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_directional_billboard_size")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.billboardEntity_setSize("@@lightSource", Vec2(arguments[0].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_directional_billboard_size")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.billboardEntity_getSize("@@lightSource").x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_disable_spot")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableSpotLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_spot_color")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_intensity")
	{
		auto types = { ScriptValueType::DECIMAL };

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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_spot_intensity")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_angle")
	{
		auto types = { ScriptValueType::DECIMAL };

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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_spot_angle")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingAngle();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:lighting_set_spot_distance")
	{
		auto types = { ScriptValueType::DECIMAL };

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
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:lighting_get_spot_distance")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
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