#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCameraCollisionHandler()->setCameraBox(Box(left, right, bottom, top, back, front));
}

void EngineInterface::collision_enableCameraResponse(bool x, bool y, bool z)
{
	if(_core->getCameraCollisionHandler()->isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: already enabled!");
		return;
	}

	_core->getCameraCollisionHandler()->enableCameraAabbResponse(x, y, z);
}

void EngineInterface::collision_disableCameraResponse()
{
	if(!_core->getCameraCollisionHandler()->isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: not enabled!");
		return;
	}

	_core->getCameraCollisionHandler()->disableCameraAabbResponse();
}

void EngineInterface::collision_enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if(_core->getCameraCollisionHandler()->isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: already enabled!");
		return;
	}

	_core->getCameraCollisionHandler()->enableCameraTerrainResponse(cameraHeight, cameraSpeed);
}

void EngineInterface::collision_disableTerrainResponse()
{
	if(!_core->getCameraCollisionHandler()->isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: not enabled!");
		return;
	}

	_core->getCameraCollisionHandler()->disableCameraTerrainResponse();
}