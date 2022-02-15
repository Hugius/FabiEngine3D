#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->aabb_isExisting(id))
	{
		_throwRuntimeError("AABB does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad3d_isExisting("@" + id))
		{
			_throwRuntimeError("template quad3D does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad3d_isExisting(id))
		{
			_throwRuntimeError("quad3D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text3d_isExisting("@" + id))
		{
			_throwRuntimeError("template text3D does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text3d_isExisting(id))
		{
			_throwRuntimeError("text3D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad2d_isExisting("@" + id))
		{
			_throwRuntimeError("template quad2D does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad2d_isExisting(id))
		{
			_throwRuntimeError("quad2D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text2d_isExisting("@" + id))
		{
			_throwRuntimeError("template text2D does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text2d_isExisting(id))
		{
			_throwRuntimeError("text2D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dPointlight(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->pointlight_isExisting(id))
	{
		_throwRuntimeError("pointlight does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSpotlight(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->spotlight_isExisting(id))
	{
		_throwRuntimeError("spotlight does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModel(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->model_isExisting("@" + id))
		{
			_throwRuntimeError("template model does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->model_isExisting(id))
		{
			_throwRuntimeError("model does not exist");
			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string& modelId, const string& partId)
{
	if(_fe3d->model_hasPart(modelId, partId))
	{
		_throwRuntimeError("model part does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dReflection(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->reflection_isExisting(id))
	{
		_throwRuntimeError("reflection does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sky_isExisting("@" + id))
		{
			_throwRuntimeError("template sky does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sky_isExisting(id))
		{
			_throwRuntimeError("sky does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->terrain_isExisting("@" + id))
		{
			_throwRuntimeError("template terrain does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->terrain_isExisting(id))
		{
			_throwRuntimeError("terrain does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation2d(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->animation2d_isExisting(id))
	{
		_throwRuntimeError("animation2D does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation3d(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->animation3d_isExisting(id))
	{
		_throwRuntimeError("animation3D does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->water_isExisting("@" + id))
		{
			_throwRuntimeError("template water does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->water_isExisting(id))
		{
			_throwRuntimeError("water does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound2d_isExisting("@" + id))
		{
			_throwRuntimeError("template sound does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound2d_isExisting(id))
		{
			_throwRuntimeError("sound2D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound3d_isExisting("@" + id))
		{
			_throwRuntimeError("template sound does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound3d_isExisting(id))
		{
			_throwRuntimeError("sound3D does not exist");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dId(const string& id)
{
	if(any_of(id.begin(), id.end(), isspace))
	{
		_throwRuntimeError("ID cannot contain any spaces");
		return false;
	}

	if(!all_of(id.begin(), id.end(), isalnum))
	{
		_throwRuntimeError("ID cannot contain any specials");
		return false;
	}

	if(any_of(id.begin(), id.end(), isupper))
	{
		_throwRuntimeError("ID cannot contain any capitals");
		return false;
	}

	return true;
}