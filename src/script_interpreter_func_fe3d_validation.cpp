#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string & aabbId, bool isTemplate)
{
	if(!_validateFe3dId(aabbId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->aabb_isExisting("@" + aabbId))
		{
			_throwRuntimeError("template AABB does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->aabb_isExisting(aabbId))
		{
			_throwRuntimeError("AABB does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad3d(const string & quad3dId, bool isTemplate)
{
	if(!_validateFe3dId(quad3dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad3d_isExisting("@" + quad3dId))
		{
			_throwRuntimeError("template quad3D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->quad3d_isExisting(quad3dId))
		{
			_throwRuntimeError("quad3D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText3d(const string & text3dId, bool isTemplate)
{
	if(!_validateFe3dId(text3dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text3d_isExisting("@" + text3dId))
		{
			_throwRuntimeError("template text3D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->text3d_isExisting(text3dId))
		{
			_throwRuntimeError("text3D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad2d(const string & quad2dId, bool isTemplate)
{
	if(!_validateFe3dId(quad2dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad2d_isExisting("@" + quad2dId))
		{
			_throwRuntimeError("template quad2D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->quad2d_isExisting(quad2dId))
		{
			_throwRuntimeError("quad2D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText2d(const string & text2dId, bool isTemplate)
{
	if(!_validateFe3dId(text2dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text2d_isExisting("@" + text2dId))
		{
			_throwRuntimeError("template text2D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->text2d_isExisting(text2dId))
		{
			_throwRuntimeError("text2D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dPointlight(const string & pointlightId, bool isTemplate)
{
	if(!_validateFe3dId(pointlightId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->pointlight_isExisting("@" + pointlightId))
		{
			_throwRuntimeError("template pointlight does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->pointlight_isExisting(pointlightId))
		{
			_throwRuntimeError("pointlight does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSpotlight(const string & spotlightId)
{
	if(!_validateFe3dId(spotlightId))
	{
		return false;
	}

	if(!_fe3d->spotlight_isExisting(spotlightId))
	{
		_throwRuntimeError("spotlight does not exist");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModel(const string & modelId, bool isTemplate)
{
	if(!_validateFe3dId(modelId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->model_isExisting("@" + modelId))
		{
			_throwRuntimeError("template model does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->model_isExisting(modelId))
		{
			_throwRuntimeError("model does not exist");

			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string & modelId, const string & partId)
{
	if(_fe3d->model_hasPart(modelId, partId))
	{
		_throwRuntimeError("model part does not exist");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dCaptor(const string & captorId)
{
	if(!_validateFe3dId(captorId))
	{
		return false;
	}

	if(!_fe3d->captor_isExisting(captorId))
	{
		_throwRuntimeError("captor does not exist");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky(const string & skyId, bool isTemplate)
{
	if(!_validateFe3dId(skyId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sky_isExisting("@" + skyId))
		{
			_throwRuntimeError("template sky does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->sky_isExisting(skyId))
		{
			_throwRuntimeError("sky does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain(const string & terrainId, bool isTemplate)
{
	if(!_validateFe3dId(terrainId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->terrain_isExisting("@" + terrainId))
		{
			_throwRuntimeError("template terrain does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->terrain_isExisting(terrainId))
		{
			_throwRuntimeError("terrain does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation2d(const string & animation2dId)
{
	if(!_validateFe3dId(animation2dId))
	{
		return false;
	}

	if(!_fe3d->animation2d_isExisting(animation2dId))
	{
		_throwRuntimeError("animation2D does not exist");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation3d(const string & animation3dId)
{
	if(!_validateFe3dId(animation3dId))
	{
		return false;
	}

	if(!_fe3d->animation3d_isExisting(animation3dId))
	{
		_throwRuntimeError("animation3D does not exist");

		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater(const string & waterId, bool isTemplate)
{
	if(!_validateFe3dId(waterId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->water_isExisting("@" + waterId))
		{
			_throwRuntimeError("template water does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->water_isExisting(waterId))
		{
			_throwRuntimeError("water does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound2d(const string & sound2dId, bool isTemplate)
{
	if(!_validateFe3dId(sound2dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound2d_isExisting("@" + sound2dId))
		{
			_throwRuntimeError("template sound2D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->sound2d_isExisting(sound2dId))
		{
			_throwRuntimeError("sound2D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3d(const string & sound3dId, bool isTemplate)
{
	if(!_validateFe3dId(sound3dId))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound3d_isExisting("@" + sound3dId))
		{
			_throwRuntimeError("template sound2D does not exist");

			return false;
		}
	}
	else
	{
		if(!_fe3d->sound3d_isExisting(sound3dId))
		{
			_throwRuntimeError("sound3D does not exist");

			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dId(const string & id)
{
	if(id.empty())
	{
		_throwRuntimeError("ID cannot be empty");

		return false;
	}

	if(any_of(id.begin(), id.end(), isspace))
	{
		_throwRuntimeError("ID cannot contain any spaces");

		return false;
	}

	if(any_of(id.begin(), id.end(), isupper))
	{
		_throwRuntimeError("ID cannot contain any capitals");

		return false;
	}

	return true;
}