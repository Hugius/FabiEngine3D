#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dTerrainSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:terrain_set_lightness")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate terrain existence
			if (_validateFe3dTerrain())
			{
				_fe3d.terrainEntity_setLightness(_fe3d.terrainEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute terrain functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as a networking server!");
	}

	// Return
	return true;
}