#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSkyGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sky_get_mix_id")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getMixID();
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_mix_value")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getMixValue();
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_lightness")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getLightness(_fe3d->sky_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_r")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_g")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_b")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_rotation")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_getRotation(_fe3d->sky_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_is_wireframed")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				auto result = _fe3d->sky_isWireframed(_fe3d->sky_getSelectedID());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sky` functionality as networking server!");
	}

	return true;
}