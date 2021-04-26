#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dWaterEntity()
{
	// Check if entity exists
	if (_fe3d.waterEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no water entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dWaterEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:water_set_speed")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:water_get_speed_x")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				auto result = _fe3d.waterEntity_getSpeed(_fe3d.waterEntity_getSelectedID()).x;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:water_get_speed_z")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				auto result = _fe3d.waterEntity_getSpeed(_fe3d.waterEntity_getSelectedID()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:water_get_height")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				auto result = _fe3d.waterEntity_getPosition(_fe3d.waterEntity_getSelectedID()).y;
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:water_set_color")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
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
	else if (functionName == "fe3d:water_get_color")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				auto result = _fe3d.waterEntity_getColor(_fe3d.waterEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:water_set_transparency")
	{
		auto types = { ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				_fe3d.waterEntity_setTransparency(_fe3d.waterEntity_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:water_get_transparency")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate water existence
			if (_validateFe3dWaterEntity())
			{
				auto result = _fe3d.waterEntity_getTransparency(_fe3d.waterEntity_getSelectedID());
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