#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:water_get_speed_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpeed(_fe3d.water_getSelectedID()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_speed_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getSpeed(_fe3d.water_getSelectedID()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_height")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getHeight(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getColor(_fe3d.water_getSelectedID()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:water_get_transparency")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dWater())
			{
				auto result = _fe3d.water_getTransparency(_fe3d.water_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
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
		_throwScriptError("cannot access `fe3d:water` functionality as networking server!");
	}

	// Return
	return true;
}