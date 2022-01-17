#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_fe3d->aabb_isExisting(ID))
	{
		_throwScriptError("AABB entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dBillboard(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->billboard_isExisting("@" + ID))
		{
			_throwScriptError("template billboard entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->billboard_isExisting(ID))
		{
			_throwScriptError("billboard entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dQuad2d(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->quad2d_isExisting("@" + ID))
		{
			_throwScriptError("template quad2d entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->quad2d_isExisting(ID))
		{
			_throwScriptError("Quad2D entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->text_isExisting("@" + ID))
		{
			_throwScriptError("template text entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->text_isExisting(ID))
		{
			_throwScriptError("text entity does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dPointlight(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_fe3d->pointlight_isExisting(ID))
	{
		_throwScriptError("pointlight entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSpotlight(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_fe3d->spotlight_isExisting(ID))
	{
		_throwScriptError("spotlight entity does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModel(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->model_isExisting("@" + ID))
		{
			_throwScriptError("template model entity does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->model_isExisting(ID))
		{
			_throwScriptError("model entity does not exist!");
			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string& modelID, const string& partID)
{
	if(_fe3d->model_hasPart(modelID, partID))
	{
		_throwScriptError("model entity part does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dReflection(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_fe3d->reflection_isExisting(ID))
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

const bool ScriptInterpreter::_validateFe3dAnimation2d(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_animation2dEditor->isAnimationExisting(ID))
	{
		_throwScriptError("animation2D does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dAnimation3d(const string& ID)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(!_animation3dEditor->isAnimationExisting(ID))
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

const bool ScriptInterpreter::_validateFe3dSound2d(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound2d_isExisting("@" + ID))
		{
			_throwScriptError("template sound does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound2d_isExisting(ID))
		{
			_throwScriptError("sound2D does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3d(const string& ID, bool isTemplate)
{
	if(!_validateFe3dID(ID))
	{
		return false;
	}

	if(isTemplate)
	{
		if(!_fe3d->sound3d_isExisting("@" + ID))
		{
			_throwScriptError("template sound does not exist!");
			return false;
		}
	}
	else
	{
		if(!_fe3d->sound3d_isExisting(ID))
		{
			_throwScriptError("sound3D does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dID(const string& ID)
{
	if(ID.find(' ') != string::npos)
	{
		_throwScriptError("ID cannot contain spaces!");
		return false;
	}

	if(ID.find('@') != string::npos)
	{
		_throwScriptError("ID cannot contain '@'!");
		return false;
	}

	return true;
}