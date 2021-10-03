#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dSkyGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine function type
	if (functionName == "fe3d:sky_get_mix_id")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSky())
			{
				auto result = _fe3d.skyEntity_getMixID();
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_mix_value")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSky())
			{
				auto result = _fe3d.skyEntity_getMixValue();
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_rotation_speed")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSky())
			{
				auto result = _fe3d.skyEntity_getRotationSpeed(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_lightness")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSky())
			{
				auto result = _fe3d.skyEntity_getLightness(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:sky_get_color")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate sky existence
			if (_validateFe3dSky())
			{
				auto result = _fe3d.skyEntity_getColor(_fe3d.skyEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sky functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sky` functionality as a networking server!");
	}

	// Return
	return true;
}