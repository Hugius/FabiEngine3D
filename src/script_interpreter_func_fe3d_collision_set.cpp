#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:collision_set_camera_box")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraBox(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_aabb_response_enabled")
	{
		auto types = {SVT::BOOLEAN, SVT::BOOLEAN, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraAabbResponseEnabled(args[0]->getBoolean(), args[1]->getBoolean(), args[2]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_terrain_response_enabled")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraTerrainResponseEnabled(args[0]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_terrain_response_height")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraTerrainResponseHeight(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_terrain_response_speed")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraTerrainResponseSpeed(args[0]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:collision` functionality as networking server!");
		return true;
	}

	return true;
}