#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSkyGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:sky_get_selected_id")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->sky_getSelectedId();

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:sky_get_lightness")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getLightness(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedId()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getColor(_fe3d->sky_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedId()).r;
				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedId()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getWireframeColor(_fe3d->sky_getSelectedId()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_rotation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getRotation(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_isWireframed(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_left_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getLeftCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_right_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getRightCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_bottom_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getBottomCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_top_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getTopCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_back_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getBackCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_get_front_cube_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_getFrontCubeMapPath(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_left_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasLeftCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_right_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasRightCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_bottom_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasBottomCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_top_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasTopCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_back_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasBackCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sky_has_front_cube_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				const auto result = _fe3d->sky_hasFrontCubeMap(_fe3d->sky_getSelectedId());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:sky` functionality as a networking server");
		return true;
	}

	return true;
}