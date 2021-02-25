#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dLightingFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:graphics_set_ambient_light_color") // Set ambient lighting color
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getAmbientLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_ambient_light_color") // Get ambient lighting color
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_ambient_light_intensity") // Set ambient lighting intensity
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableAmbientLighting(_fe3d.gfx_getAmbientLightingColor(), arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_ambient_light_intensity") // Get ambient lighting intensity
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_directional_light_position") // Set directional lighting position
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:graphics_get_directional_light_position") // Get directional lighting position
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingPosition();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_directional_light_color") // Set directional lighting color
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getDirectionalLightingIntensity());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_directional_light_color") // Get directional lighting color
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_directional_light_intensity") // Set directional lighting intensity
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableDirectionalLighting(
				_fe3d.gfx_getDirectionalLightingPosition(),
				_fe3d.gfx_getDirectionalLightingColor(),
				arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_directional_light_intensity") // Get directional lighting intensity
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_enable_spot_light") // Enable spotlighting
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_spot_light") // Disable spotlighting
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableSpotLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_set_spot_light_color") // Set spot lighting color
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableSpotLighting(
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_spot_light_color") // Get spot lighting color
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_spot_light_intensity") // Set spot lighting intensity
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				arguments[0].getDecimal(),
				_fe3d.gfx_getSpotLightingAngle(),
				_fe3d.gfx_getSpotLightingDistance());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_spot_light_intensity") // Get spot lighting intensity
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_spot_light_angle") // Set spot lighting angle
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				arguments[0].getDecimal(),
				_fe3d.gfx_getSpotLightingDistance());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_spot_light_angle") // Get spot lighting angle
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingAngle();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_spot_light_distance") // Set spot lighting distance
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableSpotLighting(
				_fe3d.gfx_getSpotLightingColor(),
				_fe3d.gfx_getSpotLightingIntensity(),
				_fe3d.gfx_getSpotLightingAngle(),
				arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_spot_light_distance") // Get spot lighting distance
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getSpotLightingDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_min_distance") // Set fog min distance
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(arguments[0].getDecimal(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_min_distance") // Get fog min distance
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMinDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_max_distance") // Set fog max distance
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogThickness(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_max_distance") // Get fog max distance
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogMaxDistance();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_thickness") // Set fog thickness
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), arguments[0].getDecimal(), _fe3d.gfx_getFogColor());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_thickness") // Get fog thickness
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogThickness();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL));
		}
	}
	else if (functionName == "fe3d:graphics_set_fog_color") // Set fog color
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_enableFog(_fe3d.gfx_getFogMinDistance(), _fe3d.gfx_getFogMaxDistance(), _fe3d.gfx_getFogThickness(),
				Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_get_fog_color") // Get fog color
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getFogColor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3));
		}
	}
	else if (functionName == "fe3d:graphics_set_shadow_position") // Set shadow position
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
	else if (functionName == "fe3d:graphics_get_shadow_position") // Get shadow position
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getShadowEyePosition();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3));
		}
	}
	else if (functionName == "fe3d:graphics_enable_light_mapping") // Enable lightmapping
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableLightMapping();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_light_mapping") // Disable lightmapping
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableLightMapping();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_enable_point_lighting") // Enable pointlighting
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enablePointLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:graphics_disable_point_lighting") // Disable pointlighting
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disablePointLighting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}