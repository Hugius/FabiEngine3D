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
				const auto result = _fe3d->sky_getMixID();

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
				const auto result = _fe3d->sky_getMixValue();

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
				const auto result = _fe3d->sky_getLightness(_fe3d->sky_getSelectedID());

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
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).r;

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
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).g;

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
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedID()).b;

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
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).r;
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
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).g;

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
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedID()).b;

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
				const auto result = _fe3d->sky_getRotation(_fe3d->sky_getSelectedID());

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
				const auto result = _fe3d->sky_isWireframed(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_left_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getLeftCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_right_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getRightCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_bottom_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getBottomCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_top_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getTopCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_back_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getBackCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_front_cube_map_path")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_getFrontCubeMapPath(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_left_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasLeftCubeMap(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_right_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasRightCubeMap(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_bottom_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasBottomCubeMap(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_top_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasTopCubeMap(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_back_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasBackCubeMap(_fe3d->sky_getSelectedID());

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_front_cube_map")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dSky())
			{
				const auto result = _fe3d->sky_hasFrontCubeMap(_fe3d->sky_getSelectedID());

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