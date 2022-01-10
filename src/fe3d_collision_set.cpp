#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->getCamera()CollisionHandler->setCameraBox(Box(left, right, bottom, top, back, front));
}

void EngineInterface::collision_enableCameraResponse(bool x, bool y, bool z)
{
	if(_core->getCamera()CollisionHandler->isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: already enabled!");
		return;
	}

	_core->getCamera()CollisionHandler->enableCameraAabbResponse(x, y, z);
}

void EngineInterface::collision_disableCameraResponse()
{
	if(!_core->getCamera()CollisionHandler->isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: not enabled!");
		return;
	}

	_core->getCamera()CollisionHandler->disableCameraAabbResponse();
}

void EngineInterface::collision_enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if(_core->getCamera()CollisionHandler->isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: already enabled!");
		return;
	}

	_core->getCamera()CollisionHandler->enableCameraTerrainResponse(cameraHeight, cameraSpeed);
}

void EngineInterface::collision_disableTerrainResponse()
{
	if(!_core->getCamera()CollisionHandler->isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: not enabled!");
		return;
	}

	_core->getCamera()CollisionHandler->disableCameraTerrainResponse();
}