#include "script_action_camera.hpp"

void ScriptActionCamera::execute()
{
	_fe3d.logger_throwInfo("executed");
	// Short-hand values
	vec3 position = _fe3d.camera_getPosition();
	float yaw = _fe3d.camera_getYaw();
	float pitch = _fe3d.camera_getPitch();

	// Determine type of camera action
	if (_cameraType == CameraActionType::POSITION)
	{
		if (_cameraMethod == CameraActionMethod::MOVE) // Translate
		{
			_fe3d.camera_translate(vec3(
				_cameraDirection == CameraActionDirection::X ? _vectorArgument.x : 0.0f, 
				_cameraDirection == CameraActionDirection::Y ? _vectorArgument.y : 0.0f,
				_cameraDirection == CameraActionDirection::Z ? _vectorArgument.z : 0.0f));
		}
		else if (_cameraMethod == CameraActionMethod::SET) // Set position
		{
			_fe3d.camera_setPosition(vec3(
				_cameraDirection == CameraActionDirection::X ? _vectorArgument.x : position.x,
				_cameraDirection == CameraActionDirection::Y ? _vectorArgument.y : position.y,
				_cameraDirection == CameraActionDirection::Z ? _vectorArgument.z : position.z));
		}
	}
	else if (_cameraType == CameraActionType::YAW) // Yaw
	{
		if (_cameraMethod == CameraActionMethod::MOVE)
		{
			_fe3d.camera_setYaw(yaw + _floatArgument);
		}
		else if (_cameraMethod == CameraActionMethod::SET)
		{
			_fe3d.camera_setYaw(_floatArgument);
		}
	}
	else if (_cameraType == CameraActionType::PITCH) // Pitch
	{
		if (_cameraMethod == CameraActionMethod::MOVE)
		{
			_fe3d.camera_setPitch(pitch + _floatArgument);
		}
		else if (_cameraMethod == CameraActionMethod::SET)
		{
			_fe3d.camera_setPitch(_floatArgument);
		}
	}
	else if (_cameraType == CameraActionType::LOOKAT) // Camera lookat
	{
		if (_cameraToggle == CameraActionToggle::ON)
		{
			_fe3d.camera_enableLookat(_vectorArgument);
		}
		else if (_cameraToggle == CameraActionToggle::OFF)
		{
			_fe3d.camera_disableLookat();
		}
	}
	else if (_cameraType == CameraActionType::FIRST_PERSON) // First person view
	{
		if (_cameraToggle == CameraActionToggle::ON)
		{
			_fe3d.camera_enableFirstPersonView();
		}
		else if (_cameraToggle == CameraActionToggle::OFF)
		{
			_fe3d.camera_disableFirstPersonView();
		}
	}
}

void ScriptActionCamera::reset()
{
	_fe3d.logger_throwInfo("resetted");
}

void ScriptActionCamera::setCameraType(CameraActionType type)
{
	_cameraType = type;
}

void ScriptActionCamera::setCameraDirection(CameraActionDirection direction)
{
	_cameraDirection = direction;
}

void ScriptActionCamera::setCameraMethod(CameraActionMethod method)
{
	_cameraMethod = method;
}

void ScriptActionCamera::setCameraToggle(CameraActionToggle toggle)
{
	_cameraToggle = toggle;
}

void ScriptActionCamera::setVectorArgument(vec3 argument)
{
	_vectorArgument = argument;
}

void ScriptActionCamera::setFloatArgument(float argument)
{
	_floatArgument = argument;
}

CameraActionType ScriptActionCamera::getCameraType()
{
	return _cameraType;
}

CameraActionDirection ScriptActionCamera::getCameraDirection()
{
	return _cameraDirection;
}

CameraActionMethod ScriptActionCamera::getCameraMethod()
{
	return _cameraMethod;
}

CameraActionToggle ScriptActionCamera::getCameraToggle()
{
	return _cameraToggle;
}

vec3 ScriptActionCamera::getVectorArgument()
{
	return _vectorArgument;
}

float ScriptActionCamera::getFloatArgument()
{
	return _floatArgument;
}