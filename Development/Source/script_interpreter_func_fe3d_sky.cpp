#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dSkyEntity()
{
	// Check if entity exists
	if (_fe3d.skyEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no sky entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dSkyEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:sky_mix_with_current")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				_fe3d.skyEntity_mixWithSelected("@" + arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sky_set_mix_value")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				_fe3d.skyEntity_setMixValue(arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_mix_value")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				auto result = _fe3d.skyEntity_getMixValue();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_set_rotation_speed")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				_fe3d.skyEntity_setRotationSpeed(_fe3d.skyEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_rotation_speed")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				auto result = _fe3d.skyEntity_getRotationSpeed(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_set_lightness")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				_fe3d.skyEntity_setLightness(_fe3d.skyEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_lightness")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				auto result = _fe3d.skyEntity_getLightness(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_set_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				_fe3d.skyEntity_setColor(_fe3d.skyEntity_getSelectedID(), Vec3(
					arguments[0].getDecimal(),
					arguments[1].getDecimal(),
					arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_color")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSkyEntity())
			{
				auto result = _fe3d.skyEntity_getColor(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}