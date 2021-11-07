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
	if(!_fe3d.aabbEntity_isExisting(ID))
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
		if(!_fe3d.billboardEntity_isExisting(ID))
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
		if(!_fe3d.billboardEntity_isExisting(ID))
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
	if(!_fe3d.imageEntity_isExisting(ID))
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
	if(!_fe3d.pointlightEntity_isExisting(ID))
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
	if(!_fe3d.spotlightEntity_isExisting(ID))
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
		if(!_fe3d.modelEntity_isExisting(ID))
		{
			_throwScriptError("requested preview model with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}

		// Cannot access an instanced model
		if(_fe3d.modelEntity_isInstanced(ID))
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
		if(!_fe3d.modelEntity_isExisting(ID))
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
	if(!_fe3d.reflectionEntity_isExisting(ID))
	{
		_throwScriptError("requested reflection with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSky()
{
	// Check if entity exists
	if(_fe3d.skyEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no sky entity!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dTerrain()
{
	// Check if entity exists
	if(_fe3d.terrainEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no terrain entity!");
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
	if(!_fe3d.textEntity_isExisting(ID))
	{
		_throwScriptError("requested text with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dWater()
{
	// Check if entity exists
	if(_fe3d.waterEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no water entity!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateFe3dSound(const string& ID, bool isPreview)
{
	if(isPreview)
	{
		// Validate existence
		if(!_fe3d.sound_isExisting(ID))
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
			_throwScriptError("ID of requested sound with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if(!_fe3d.sound_isExisting(ID))
		{
			_throwScriptError("requested sound with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}