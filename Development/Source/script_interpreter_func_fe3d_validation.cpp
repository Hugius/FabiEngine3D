#include "script_interpreter.hpp"
#include "logger.hpp"

bool ScriptInterpreter::_validateFe3dAabbEntity(const string& ID)
{
	// Cannot request/delete a preview entity
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested AABB with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.aabbEntity_isExisting(ID))
	{
		_throwScriptError("requested AABB with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dBillboardEntity(const string& ID, bool isPreviewEntity)
{
	if (isPreviewEntity)
	{
		// Validate existence
		if (!_fe3d.billboardEntity_isExisting(ID))
		{
			_throwScriptError("requested preview billboard with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}
	}
	else
	{
		// Cannot access a preview billboard
		if (!isPreviewEntity && ID.front() == '@')
		{
			_throwScriptError("ID of requested billboard with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if (!_fe3d.billboardEntity_isExisting(ID))
		{
			_throwScriptError("requested billboard with ID \"" + ID + "\" does not exist!");
			return false;
		}
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dImageEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested image with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.imageEntity_isExisting(ID))
	{
		_throwScriptError("requested image with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dLightEntity(const string& ID)
{
	// Just to be consistent with not starting entity ID's with '@'
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested light with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.lightEntity_isExisting(ID))
	{
		_throwScriptError("requested light with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dModelEntity(const string& ID, bool isPreviewEntity)
{
	if (isPreviewEntity)
	{
		// Validate existence
		if (!_fe3d.modelEntity_isExisting(ID))
		{
			_throwScriptError("requested preview model with ID \"" + ID.substr(1) + "\" does not exist!");
			return false;
		}

		// Cannot access an instanced model
		if (_fe3d.modelEntity_isInstanced(ID))
		{
			_throwScriptError("requested preview model with ID \"" + ID.substr(1) + "\" cannot be instanced!");
			return false;
		}
	}
	else
	{
		// Cannot access a preview model
		if (ID.front() == '@')
		{
			_throwScriptError("ID of requested model with ID \"" + ID + "\" cannot start with '@'!");
			return false;
		}

		// Validate existence
		if (!_fe3d.modelEntity_isExisting(ID))
		{
			_throwScriptError("requested model with ID \"" + ID + "\" does not exist!");
			return false;
		}

	}

	return true;
}

bool ScriptInterpreter::_validateFe3dReflectionEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested reflection with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.reflectionEntity_isExisting(ID))
	{
		_throwScriptError("requested reflection with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dSkyEntity()
{
	// Check if entity exists
	if (_fe3d.skyEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no sky entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dTerrainEntity()
{
	// Check if entity exists
	if (_fe3d.terrainEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no terrain entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dTextEntity(const string& ID)
{
	// Cannot request/delete an engine entity
	if (ID.front() == '@')
	{
		_throwScriptError("ID of requested text with ID \"" + ID + "\" cannot start with '@'!");
		return false;
	}

	// Check if entity exists
	if (!_fe3d.textEntity_isExisting(ID))
	{
		_throwScriptError("requested text with ID \"" + ID + "\" does not exist!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_validateFe3dWaterEntity()
{
	// Check if entity exists
	if (_fe3d.waterEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no water entity!");
		return false;
	}

	return true;
}