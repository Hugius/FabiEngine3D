#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:water_set_speed")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				_fe3d.water_setSpeed(_fe3d.water_getSelectedID(),
										   fvec2(arguments[0].getDecimal() / 100000.0f, arguments[1].getDecimal() / 100000.0f));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				_fe3d.water_setColor(_fe3d.water_getSelectedID(), fvec3(
					arguments[0].getDecimal(),
					arguments[1].getDecimal(),
					arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_transparency")
	{
		auto types = {SVT::DECIMAL};

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if(_validateFe3dWater())
			{
				_fe3d.water_setTransparency(_fe3d.water_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute water functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:water` functionality as a networking server!");
	}

	// Return
	return true;
}