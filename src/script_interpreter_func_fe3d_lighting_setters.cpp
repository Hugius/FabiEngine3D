#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dLightingSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:lighting_enable_ambient")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableAmbientLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_disable_ambient")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableAmbientLighting(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_ambient_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setAmbientLightingColor(fvec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_ambient_intensity")
	{
		auto types = {SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setAmbientLightingIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_enable_directional")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_enableDirectionalLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_disable_directional")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.gfx_disableDirectionalLighting(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDirectionalLightingColor(fvec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_intensity")
	{
		auto types = {SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.gfx_setDirectionalLightingIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute lighting functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:lighting` functionality as networking server!");
	}

	return true;
}