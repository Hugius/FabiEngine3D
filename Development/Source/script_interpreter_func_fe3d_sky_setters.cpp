#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dSkySetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine function type
	if(functionName == "fe3d:sky_mix")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if(_validateFe3dSky())
			{
				_fe3d.skyEntity_selectMixSky("@" + arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_mix_value")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if(_validateFe3dSky())
			{
				_fe3d.skyEntity_setMixValue(arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_rotation_speed")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if(_validateFe3dSky())
			{
				_fe3d.skyEntity_setRotationSpeed(_fe3d.skyEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_lightness")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if(_validateFe3dSky())
			{
				_fe3d.skyEntity_setLightness(_fe3d.skyEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate sky existence
			if(_validateFe3dSky())
			{
				_fe3d.skyEntity_setColor(_fe3d.skyEntity_getSelectedID(), Vec3(
					arguments[0].getDecimal(),
					arguments[1].getDecimal(),
					arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sky functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sky` functionality as a networking server!");
	}

	// Return
	return true;
}