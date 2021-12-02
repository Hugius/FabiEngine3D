#include "script_interpreter.hpp"
#include "logger.hpp"

const bool ScriptInterpreter::_validateFe3dAabb(const string& ID)
{
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested AABB with ID \"" + ID + "\" cannot start with '@'!");
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

const bool ScriptInterpreter::_validateFe3dBillboard(const string& ID, bool isPreview)
{
	if(isPreview)
	{
		// Validate existence
		if(!_fe3d.billboard_isExisting(ID))
		{
			_throwScriptError("requested preview billboard with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ sign is reserved
		if(!isPreview && ID.front() == '@')
		{
			_throwScriptError("ID of requested billboard with ID \"" + ID + "\" cannot start with '@'!");
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
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested image with ID \"" + ID + "\" cannot start with '@'!");
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
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested pointlight with ID \"" + ID + "\" cannot start with '@'!");
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
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested spotlight with ID \"" + ID + "\" cannot start with '@'!");
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

const bool ScriptInterpreter::_validateFe3dModel(const string& ID, bool isPreview)
{
	if(isPreview)
	{
		// Validate existence
		if(!_fe3d.model_isExisting(ID))
		{
			_throwScriptError("requested preview model with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}

		// Cannot access an instanced model
		if(_fe3d.model_isInstanced(ID))
		{
			_throwScriptError("requested preview model with ID \"" + ID.substr(1) + "\" cannot be instanced!");
			return false;
		}
	}
	else
	{
		// @ sign is reserved
		if(ID.front() == '@')
		{
			_throwScriptError("ID of requested model with ID \"" + ID + "\" cannot start with '@'!");
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

const bool ScriptInterpreter::_validateFe3dReflection(const string& ID)
{
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested reflection with ID \"" + ID + "\" cannot start with '@'!");
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
	// @ sign is reserved
	if(ID.front() == '@')
	{
		_throwScriptError("ID of requested text with ID \"" + ID + "\" cannot start with '@'!");
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

const bool ScriptInterpreter::_validateFe3dSound2D(const string& ID, bool isPreview)
{
	if(isPreview)
	{
		// Validate existence
		if(!_fe3d.sound2D_isExisting(ID))
		{
			_throwScriptError("requested preview sound with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ sign is reserved
		if(!isPreview && ID.front() == '@')
		{
			_throwScriptError("ID of requested 2D sound with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.sound2D_isExisting(ID))
		{
			_throwScriptError("requested 2D sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound3D(const string& ID, bool isPreview)
{
	if (isPreview)
	{
		// Validate existence
		if (!_fe3d.sound3D_isExisting(ID))
		{
			_throwScriptError("requested preview sound with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// @ sign is reserved
		if (!isPreview && ID.front() == '@')
		{
			_throwScriptError("ID of requested 3D sound with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if (!_fe3d.sound3D_isExisting(ID))
		{
			_throwScriptError("requested 3D sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}