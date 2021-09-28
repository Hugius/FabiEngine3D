#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dWaterSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:water_set_speed")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				_fe3d.waterEntity_setSpeed(_fe3d.waterEntity_getSelectedID(), 
					Vec2(arguments[0].getDecimal() / 100000.0f, arguments[1].getDecimal() / 100000.0f));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:water_set_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				_fe3d.waterEntity_setColor(_fe3d.waterEntity_getSelectedID(), Vec3(
					arguments[0].getDecimal(), 
					arguments[1].getDecimal(),
					arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:water_set_transparency")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				_fe3d.waterEntity_setTransparency(_fe3d.waterEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute water functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:water` functionality as a networking server!");
	}

	// Return
	return true;
}