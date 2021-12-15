#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSkySetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sky_mix")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSky())
			{
				_fe3d.sky_selectMixSky("@" + arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_mix_value")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSky())
			{
				_fe3d.sky_setMixValue(arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_lightness")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSky())
			{
				_fe3d.sky_setLightness(_fe3d.sky_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSky())
			{
				_fe3d.sky_setColor(_fe3d.sky_getSelectedID(), fvec3(
					arguments[0].getDecimal(),
					arguments[1].getDecimal(),
					arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_rotation")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSky())
			{
				_fe3d.sky_setRotation(_fe3d.sky_getSelectedID(), arguments[0].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sky` functionality as networking server!");
	}

	// Return
	return true;
}