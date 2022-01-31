#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:collision_enable_camera_terrain_response")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->collision_isCameraResponseEnabled())
			{
				_throwScriptError("Tried to enable camera terrain response: already enabled!");
				return true;
			}

			_fe3d->collision_enableCameraTerrainResponse(args[0]->getDecimal(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_terrain_response")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->collision_isTerrainResponseEnabled())
			{
				_throwScriptError("Tried to enable camera terrain response: not enabled!");
				return true;
			}

			_fe3d->collision_disableCameraTerrainResponse();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_enable_camera_aabb_response")
	{
		auto types = {SVT::BOOLEAN, SVT::BOOLEAN, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->collision_isCameraResponseEnabled())
			{
				_throwScriptError("Tried to enable camera AABB response: already enabled!");
				return true;
			}

			_fe3d->collision_enableCameraAabbResponse(args[0]->getBoolean(), args[1]->getBoolean(), args[2]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_aabb_response")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->collision_isCameraResponseEnabled())
			{
				_throwScriptError("Tried to enable camera AABB response: not enabled!");
				return true;
			}

			_fe3d->collision_disableCameraAabbResponse();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_box")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraBox(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as networking server!");
	}

	return true;
}