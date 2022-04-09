#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:terrain_place")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->terrain_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("terrain already exists");
				return true;
			}

			if(_validateFe3dTerrain(args[0]->getString(), true))
			{
				_worldUtilities->copyTemplateTerrain(args[0]->getString(), ("@" + args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_select")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_select(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_lightness")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setLightness(_fe3d->terrain_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setMaxHeight(_fe3d->terrain_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setDiffuseMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setNormalMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_blend_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setBlendMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_red_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setRedDiffuseMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_green_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setGreenDiffuseMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_blue_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setBlueDiffuseMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_red_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setRedNormalMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_green_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setGreenNormalMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_blue_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setBlueNormalMap(_fe3d->terrain_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setWireframeColor(_fe3d->terrain_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular_shininess")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setSpecularShininess(_fe3d->terrain_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setSpecularIntensity(_fe3d->terrain_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_texture_repeat")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setTextureRepeat(_fe3d->terrain_getSelectedId(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_red_repeat")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setRedTextureRepeat(_fe3d->terrain_getSelectedId(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_green_repeat")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setGreenTextureRepeat(_fe3d->terrain_getSelectedId(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_blue_repeat")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setBlueTextureRepeat(_fe3d->terrain_getSelectedId(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setSpecular(_fe3d->terrain_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain(args[0]->getString(), false))
			{
				_fe3d->terrain_setWireframed(_fe3d->terrain_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:terrain` functionality as a networking server");
		return true;
	}

	return true;
}