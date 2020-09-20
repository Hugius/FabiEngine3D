#pragma once

#include "script_action.hpp"

enum class CameraActionType
{
	POSITION,
	FOLLOW,
	YAW,
	PITCH,
	LOOKAT,
	FIRST_PERSON,
	NONE
};

enum class CameraActionDirection
{
	X,
	Y,
	Z,
	XYZ,
	NONE
};

enum class CameraActionFollow
{
	FOLLOW_X,
	FOLLOW_Z,
	FOLLOW_ZY,
	NONE
};

enum class CameraActionMethod
{
	UPDATE,
	SET,
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
	void setCameraFollow(CameraActionFollow follow);
	void setCameraMethod(CameraActionMethod method);
	void setCameraToggle(CameraActionToggle toggle);
	void setVectorArgument(vec3 position);
	void setFloatArgument(float yaw);

	CameraActionType getCameraType();
	CameraActionDirection getCameraDirection();
	CameraActionFollow getCameraFollow();
	CameraActionMethod getCameraMethod();
	CameraActionToggle getCameraToggle();

	vec3 getVectorArgument();
	float getFloatArgument();

	bool hasVectorArgument();
	bool hasFloatArgument();

private:
	vec3 _vectorArgument = vec3(0.0f);
	float _floatArgument = 0.0;

	CameraActionType _cameraType = CameraActionType::NONE;
	CameraActionDirection _cameraDirection = CameraActionDirection::NONE;
	CameraActionFollow _cameraFollow = CameraActionFollow::NONE;
	CameraActionMethod _cameraMethod = CameraActionMethod::NONE;
	CameraActionToggle _cameraToggle = CameraActionToggle::NONE;

	bool _hasVectorArgument = false;
	bool _hasFloatArgument = false;
};