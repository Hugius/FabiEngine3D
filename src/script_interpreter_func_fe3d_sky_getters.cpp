#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSkyGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sky_get_mix_id")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getMixID();
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_mix_value")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getMixValue();
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_lightness")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getLightness(_fe3d.sky_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_r")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getColor(_fe3d.sky_getSelectedID()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_g")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getColor(_fe3d.sky_getSelectedID()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_b")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getColor(_fe3d.sky_getSelectedID()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_rotation")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d.sky_getRotation(_fe3d.sky_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sky functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sky` functionality as networking server!");
	}

	// Return
	return true;
}