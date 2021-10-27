#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dLightingGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:lighting_get_ambient_color")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_ambient_intensity")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getAmbientLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_position")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingPosition();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_color")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingColor();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_intensity")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.gfx_getDirectionalLightingIntensity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:lighting_get_directional_billboard_size")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.billboardEntity_getSize("@@lightSource").x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute lighting functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:lighting` functionality as a networking server!");
	}

	return true;
}