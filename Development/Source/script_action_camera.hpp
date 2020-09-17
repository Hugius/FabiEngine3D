#pragma once

#include "script_action.hpp"

enum class CameraActionType
{
	POSITION,
	PITCH,
	YAW,
	LOOKAT,
	FIRST_PERSON,
	NONE
};

enum class CameraActionDirection
{
	X,
	Y,
	Z,
	FOLLOW_X,
	FOLLOW_Z,
	FOLLOW_ZY,
	NONE
};

enum class CameraActionMethod
{
	SET,
	MOVE,
	NONE
};

class ScriptActionCamera final : public ScriptAction
{
public:
	using ScriptAction::ScriptAction;

	void execute() override;
	void reset() override;

private:
	vec3 _cameraPosition;
	vec3 _lookatPosition;
	float _pitch;
	float _yaw;

	CameraActionType _type = CameraActionType::NONE;
	CameraActionDirection _direction = CameraActionDirection::NONE;
	CameraActionMethod _method = CameraActionMethod::NONE;
};