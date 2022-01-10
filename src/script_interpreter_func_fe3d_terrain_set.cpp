#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTerrainSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:terrain_set_lightness")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setLightness(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_wireframe_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setWireframeColor(_fe3d->terrain_getSelectedID(),
												 fvec3(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular_shininess")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setSpecularShininess(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setSpecularIntensity(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_texture_repeat")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setTextureRepeat(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_red_repeat")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setRedTextureRepeat(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_green_repeat")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setGreenTextureRepeat(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_blue_repeat")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setBlueTextureRepeat(_fe3d->terrain_getSelectedID(), args[0].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_specular")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setSpecular(_fe3d->terrain_getSelectedID(), args[0].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:terrain_set_wireframed")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dTerrain())
			{
				_fe3d->terrain_setWireframed(_fe3d->terrain_getSelectedID(), args[0].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as networking server!");
	}

	return true;
}