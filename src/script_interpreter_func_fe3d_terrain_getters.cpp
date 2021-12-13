#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:terrain_get_pixel_height")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dTerrain())
			{
				float halfTerrainSize = (_fe3d.terrain_getSize(_fe3d.terrain_getSelectedID()) / 2.0f);
				auto result = _fe3d.terrain_getPixelHeight(_fe3d.terrain_getSelectedID(),
														   (arguments[0].getDecimal() + halfTerrainSize),
														   (arguments[1].getDecimal() + halfTerrainSize));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_max_height")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getMaxHeight(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_size")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getSize(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:terrain_get_lightness")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.terrain_getLightness(_fe3d.terrain_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute terrain functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as networking server!");
	}

	// Return
	return true;
}