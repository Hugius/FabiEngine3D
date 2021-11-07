#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:water_get_speed_x")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				auto result = _fe3d.waterEntity_getSpeed(_fe3d.waterEntity_getSelectedID()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_speed_z")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				auto result = _fe3d.waterEntity_getSpeed(_fe3d.waterEntity_getSelectedID()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_height")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				auto result = _fe3d.waterEntity_getHeight(_fe3d.waterEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				auto result = _fe3d.waterEntity_getColor(_fe3d.waterEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_transparency")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				auto result = _fe3d.waterEntity_getTransparency(_fe3d.waterEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute water functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:water` functionality as a networking server!");
	}

	// Return
	return true;
}