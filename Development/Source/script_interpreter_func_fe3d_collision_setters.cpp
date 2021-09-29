#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dCollisionSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:collision_enable_camera_terrain_response")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }; // CameraHeight + cameraSpeed

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_terrain_response")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableTerrainResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_set_camera_box")
	{
		// Bottom top left right front back
		auto types =
		{
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL,
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_setCameraBoxSize(
				arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal(),
				arguments[3].getDecimal(), arguments[4].getDecimal(), arguments[5].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_response")
	{
		// xResponse yResponse zResponse
		auto types =
		{
			ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN
		};

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraResponse(arguments[0].getBoolean(), arguments[1].getBoolean(), arguments[2].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_response")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute collision functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as a networking server!");
	}

	return true;
}