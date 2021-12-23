#include "script_interpreter.hpp"
#include "logger.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested AABB with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.aabb_isExisting(ID))
	{
		_throwScriptError("requested AABB with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dBillboard(const string& ID, bool isTemplate)
{
	if(isTemplate)
	{
		// Validate existence
		if(!_fe3d.billboard_isExisting(ID))
		{
			_throwScriptError("requested template billboard with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ signs not allowed
		if(!isTemplate && ID[0] == '@')
		{
			_throwScriptError("ID of requested billboard with ID \"" + ID + "\" cannot contain '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.billboard_isExisting(ID))
		{
			_throwScriptError("requested billboard with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dImage(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested image with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.image_isExisting(ID))
	{
		_throwScriptError("requested image with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dPointlight(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested pointlight with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.pointlight_isExisting(ID))
	{
		_throwScriptError("requested pointlight with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSpotlight(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested spotlight with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.spotlight_isExisting(ID))
	{
		_throwScriptError("requested spotlight with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModel(const string& ID, bool isTemplate)
{
	if(isTemplate)
	{
		// Validate existence
		if(!_fe3d.model_isExisting(ID))
		{
			_throwScriptError("requested template model with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}

		// Cannot access an instanced model
		if(_fe3d.model_isInstanced(ID))
		{
			_throwScriptError("requested template model with ID \"" + ID.substr(1) + "\" cannot be instanced!");
			return false;
		}
	}
	else
	{
		// @ signs not allowed
		if(ID[0] == '@')
		{
			_throwScriptError("ID of requested model with ID \"" + ID + "\" cannot contain '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.model_isExisting(ID))
		{
			_throwScriptError("requested model with ID \"" + ID + "\" does not exist!");
			return false;
		}

	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dModelPart(const string& modelID, const string& partID)
{
	// Check if part exists
	if(_fe3d.model_hasPart(modelID, partID))
	{
		_throwScriptError("requested model with ID \"" + modelID + "\" has no part with ID \"" + partID + "\"!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dReflection(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested reflection with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.reflection_isExisting(ID))
	{
		_throwScriptError("requested reflection with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky()
{
	// Check if entity exists
	if(_fe3d.sky_getSelectedID().empty())
	{
		_throwScriptError("current world has no sky entity!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain()
{
	// Check if entity exists
	if(_fe3d.terrain_getSelectedID().empty())
	{
		_throwScriptError("current world has no terrain entity!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dText(const string& ID)
{
	// @ signs not allowed
	if(ID[0] == '@')
	{
		_throwScriptError("ID of requested text with ID \"" + ID + "\" cannot contain '@'!");
		return false;
	}

	// Check if entity exists
	if(!_fe3d.text_isExisting(ID))
	{
		_throwScriptError("requested text with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater()
{
	// Check if entity exists
	if(_fe3d.water_getSelectedID().empty())
	{
		_throwScriptError("current world has no water entity!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound2d(const string& ID, bool isTemplate)
{
	if(isTemplate)
	{
		// Validate existence
		if(!_fe3d.sound2d_isExisting(ID))
		{
			_throwScriptError("requested template sound with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ signs not allowed
		if(!isTemplate && ID[0] == '@')
		{
			_throwScriptError("ID of requested 2D sound with ID \"" + ID + "\" cannot contain '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.sound2d_isExisting(ID))
		{
			_throwScriptError("requested 2D sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3d(const string& ID, bool isTemplate)
{
	if(isTemplate)
	{
		// Validate existence
		if(!_fe3d.sound3d_isExisting(ID))
		{
			_throwScriptError("requested template sound with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ signs not allowed
		if(!isTemplate && ID[0] == '@')
		{
			_throwScriptError("ID of requested 3D sound with ID \"" + ID + "\" cannot contain '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.sound3d_isExisting(ID))
		{
			_throwScriptError("requested 3D sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}