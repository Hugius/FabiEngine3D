#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_fe3d->aabb_isExisting(id))
	{
		_throwRuntimeError("AABB entity does not exist");
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
			_throwRuntimeError("template quad3d entity does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad3d_isExisting(id))
		{
			_throwRuntimeError("quad3d entity does not exist");
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
			_throwRuntimeError("template text3d entity does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text3d_isExisting(id))
		{
			_throwRuntimeError("text3d entity does not exist");
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
			_throwRuntimeError("template Quad2D entity does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad2d_isExisting(id))
		{
			_throwRuntimeError("Quad2D entity does not exist");
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
			_throwRuntimeError("template Text2D entity does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text2d_isExisting(id))
		{
			_throwRuntimeError("Text2D entity does not exist");
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
		_throwRuntimeError("pointlight entity does not exist");
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
		_throwRuntimeError("spotlight entity does not exist");
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
			_throwRuntimeError("template model entity does not exist");
			return false;
		}
	}
	else
	{
		if(!_fe3d->model_isExisting(id))
		{
			_throwRuntimeError("model entity does not exist");
			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string& modelId, const string& partId)
{
	if(_fe3d->model_hasPart(modelId, partId))
	{
		_throwRuntimeError("model entity part does not exist");
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
		_throwRuntimeError("reflection entity does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky()
{
	if(_fe3d->sky_getSelectedId().empty())
	{
		_throwRuntimeError("sky entity not selected");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain()
{
	if(_fe3d->terrain_getSelectedId().empty())
	{
		_throwRuntimeError("terrain entity not selected");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation2d(const string& id)
{
	if(!_validateFe3dId(id))
	{
		return false;
	}

	if(!_animation2dEditor->isAnimationExisting(id))
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

	if(!_animation3dEditor->isAnimationExisting(id))
	{
		_throwRuntimeError("animation3D does not exist");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater()
{
	if(_fe3d->water_getSelectedId().empty())
	{
		_throwRuntimeError("water entity not selected");
		return false;
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
	if(id.find('@') != string::npos)
	{
		_throwRuntimeError("id cannot contain '@'");
		return false;
	}

	if(id.find(' ') != string::npos)
	{
		_throwRuntimeError("id cannot contain spaces");
		return false;
	}

	return true;
}