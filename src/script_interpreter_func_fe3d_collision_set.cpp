#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:collision_enable_camera_terrain_response")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d.collision_enableTerrainResponse(args[0].getDecimal(), args[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_terrain_response")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d.collision_disableTerrainResponse();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_enable_camera_response")
	{
		auto types = {SVT::BOOLEAN, SVT::BOOLEAN, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d.collision_enableCameraResponse(args[0].getBoolean(), args[1].getBoolean(), args[2].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_response")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_box")
	{
		// Bottom top left right front back
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d.collision_setCameraBox(
				args[0].getDecimal(), args[1].getDecimal(),
				args[2].getDecimal(), args[3].getDecimal(),
				args[4].getDecimal(), args[5].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as networking server!");
	}

	return true;
}