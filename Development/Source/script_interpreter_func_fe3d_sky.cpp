#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dSkyEntity()
{
	// Check if entity exists
	if (_fe3d.skyEntity_getSelectedID().empty())
	{
		_throwScriptError("Current scene has no sky entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dSkyEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:sky_mix_with_current") // Mix a skyEntity with the currently selected skyEntity
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
	else if (functionName == "fe3d:sky_set_mix_value") // Set skyEntity mix value
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
	else if (functionName == "fe3d:sky_get_mix_value") // Get skyEntity mix value
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
	else if (functionName == "fe3d:sky_set_rotation_speed") // Set skyEntity rotation spped
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
	else if (functionName == "fe3d:sky_get_rotation_speed") // Get skyEntity rotation spped
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
	else
	{
		return false;
	}

	return true;
}