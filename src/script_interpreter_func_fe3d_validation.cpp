#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_fe3d->aabb_isExisting(id))
	{
		_throwScriptError("AABB entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad3d_isExisting("@" + id))
		{
			_throwScriptError("template quad3d entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad3d_isExisting(id))
		{
			_throwScriptError("quad3d entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text3d_isExisting("@" + id))
		{
			_throwScriptError("template text3d entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text3d_isExisting(id))
		{
			_throwScriptError("text3d entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad2d_isExisting("@" + id))
		{
			_throwScriptError("template Quad2D entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad2d_isExisting(id))
		{
			_throwScriptError("Quad2D entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text2d_isExisting("@" + id))
		{
			_throwScriptError("template Text2D entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text2d_isExisting(id))
		{
			_throwScriptError("Text2D entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dPointlight(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_fe3d->pointlight_isExisting(id))
	{
		_throwScriptError("pointlight entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSpotlight(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_fe3d->spotlight_isExisting(id))
	{
		_throwScriptError("spotlight entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModel(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->model_isExisting("@" + id))
		{
			_throwScriptError("template model entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->model_isExisting(id))
		{
			_throwScriptError("model entity does not exist!");
			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string& modelId, const string& partId)
{
	if(_fe3d->model_hasPart(modelId, partId))
	{
		_throwScriptError("model entity part does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dReflection(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_fe3d->reflection_isExisting(id))
	{
		_throwScriptError("reflection entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky()
{
	if(_fe3d->sky_getSelectedID().empty())
	{
		_throwScriptError("sky entity not selected!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain()
{
	if(_fe3d->terrain_getSelectedID().empty())
	{
		_throwScriptError("terrain entity not selected!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation2d(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_animation2dEditor->isAnimationExisting(id))
	{
		_throwScriptError("animation2D does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation3d(const string& id)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(!_animation3dEditor->isAnimationExisting(id))
	{
		_throwScriptError("animation3D does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater()
{
	if(_fe3d->water_getSelectedID().empty())
	{
		_throwScriptError("water entity not selected!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound2d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound2d_isExisting("@" + id))
		{
			_throwScriptError("template sound does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound2d_isExisting(id))
		{
			_throwScriptError("sound2D does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3d(const string& id, bool isTemplate)
{
	if(!_validateFe3dID(id))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound3d_isExisting("@" + id))
		{
			_throwScriptError("template sound does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound3d_isExisting(id))
		{
			_throwScriptError("sound3D does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dID(const string& id)
{
	if(id.find(' ') != string::npos)
	{
		_throwScriptError("id cannot contain spaces!");
		return false;
	}

	if(id.find('@') != string::npos)
	{
		_throwScriptError("id cannot contain '@'!");
		return false;
	}

	return true;
}