#include "camera_collision_handler.hpp"

using std::make_shared;

CameraCollisionHandler::CameraCollisionHandler()
{
	_cameraBox = make_shared<Box>(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void CameraCollisionHandler::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void CameraCollisionHandler::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void CameraCollisionHandler::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void CameraCollisionHandler::setCameraBox(const shared_ptr<Box> value)
{
	_cameraBox = value;
}

void CameraCollisionHandler::setCameraAabbResponseEnabled(bool x, bool y, bool z)
{
	_isCameraAabbResponseEnabledX = x;
	_isCameraAabbResponseEnabledY = y;
	_isCameraAabbResponseEnabledZ = z;
}

void CameraCollisionHandler::setCameraTerrainResponseEnabled(bool value)
{
	_isCameraTerrainResponseEnabled = value;
}

void CameraCollisionHandler::setCameraTerrainResponseHeight(float value)
{
	_cameraTerrainResponseHeight = value;
}

void CameraCollisionHandler::setCameraTerrainResponseSpeed(float value)
{
	_cameraTerrainResponseSpeed = value;
}

const float CameraCollisionHandler::getCameraTerrainResponseHeight() const
{
	return _cameraTerrainResponseHeight;
}

const float CameraCollisionHandler::getCameraTerrainResponseSpeed() const
{
	return _cameraTerrainResponseSpeed;
}

const bool CameraCollisionHandler::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledX() const
{
	return _isCameraAabbResponseEnabledX;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledY() const
{
	return _isCameraAabbResponseEnabledY;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledZ() const
{
	return _isCameraAabbResponseEnabledZ;
}

const bool CameraCollisionHandler::isCameraTerrainResponseEnabled() const
{
	return _isCameraTerrainResponseEnabled;
}