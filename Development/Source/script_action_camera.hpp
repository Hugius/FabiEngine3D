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

enum class CameraActionToggle
{
	ON,
	OFF,
	NONE
};

class ScriptActionCamera final : public ScriptAction
{
public:
	using ScriptAction::ScriptAction;

	void execute() override;
	void reset() override;

	void setCameraType(CameraActionType type);
	void setCameraDirection(CameraActionDirection direction);
	void setCameraMethod(CameraActionMethod method);
	void setCameraToggle(CameraActionToggle toggle);
	void setVectorArgument(vec3 position);
	void setFloatArgument(float yaw);

	CameraActionType getCameraType();
	CameraActionDirection getCameraDirection();
	CameraActionMethod getCameraMethod();
	CameraActionToggle getCameraToggle();

	vec3 getVectorArgument();
	float getFloatArgument();

private:
	vec3 _vectorArgument = vec3(0.0f);
	float _floatArgument = 0.0;

	CameraActionType _cameraType = CameraActionType::NONE;
	CameraActionDirection _cameraDirection = CameraActionDirection::NONE;
	CameraActionMethod _cameraMethod = CameraActionMethod::NONE;
	CameraActionToggle _cameraToggle = CameraActionToggle::NONE;
};