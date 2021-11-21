#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dLightingSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:lighting_enable_ambient")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableAmbientLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_disable_ambient")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableAmbientLighting(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_ambient_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_setAmbientLightingColor(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_ambient_intensity")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_setAmbientLightingIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_enable_directional")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_enableDirectionalLighting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_disable_directional")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.gfx_disableDirectionalLighting(false);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_position")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto position = Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal());
			_fe3d.gfx_setDirectionalLightingPosition(position);
			_fe3d.billboard_setPosition("@@directionalLightSource", position);
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_color")
	{
		auto types = { SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_setDirectionalLightingColor(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_intensity")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.gfx_setDirectionalLightingIntensity(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:lighting_set_directional_billboard_size")
	{
		auto types = { SVT::DECIMAL };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.billboard_setSize("@@directionalLightSource", Vec2(arguments[0].getDecimal()));
			_fe3d.billboard_setVisible("@@directionalLightSource", (arguments[0].getDecimal() != 0.0f));
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
		_throwScriptError("cannot access `fe3d:lighting` functionality as a networking server!");
	}

	return true;
}