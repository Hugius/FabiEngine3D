#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::collision_setCameraBox(float left, float right, float bottom, float top, float back, float front)
{
	_core->_cameraCollisionHandler.setCameraBox(Box(left, right, bottom, top, back, front));
}

void FabiEngine3D::collision_enableCameraResponse(bool x, bool y, bool z)
{
	if(_core->_cameraCollisionHandler.isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: already enabled!");
		return;
	}

	_core->_cameraCollisionHandler.enableCameraAabbResponse(x, y, z);
}

void FabiEngine3D::collision_disableCameraResponse()
{
	if(!_core->_cameraCollisionHandler.isCameraAabbResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera AABB response: not enabled!");
		return;
	}

	_core->_cameraCollisionHandler.disableCameraAabbResponse();
}

void FabiEngine3D::collision_enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if(_core->_cameraCollisionHandler.isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: already enabled!");
		return;
	}

	_core->_cameraCollisionHandler.enableCameraTerrainResponse(cameraHeight, cameraSpeed);
}

void FabiEngine3D::collision_disableTerrainResponse()
{
	if(!_core->_cameraCollisionHandler.isCameraTerrainResponseEnabled())
	{
		Logger::throwWarning("Tried to enable camera terrain response: not enabled!");
		return;
	}

	_core->_cameraCollisionHandler.disableCameraTerrainResponse();
}