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

void CameraCollisionHandler::setCameraBox(shared_ptr<Box> value)
{
	_cameraBox = value;
}

void CameraCollisionHandler::setCameraTerrainResponseHeight(float value)
{
	_cameraTerrainResponseHeight = value;
}

void CameraCollisionHandler::setCameraTerrainResponseSpeed(float value)
{
	_cameraTerrainResponseSpeed = value;
}

void CameraCollisionHandler::resetTerrainStatus(const string & terrainId)
{
	if(terrainId == _terrainId)
	{
		_terrainId = "";
	}
}

void CameraCollisionHandler::resetAabbStatus(const string & aabbId)
{
	if(_aabbCollisions.find(aabbId) != _aabbCollisions.end())
	{
		_aabbCollisions.erase(aabbId);
	}
}

const pair<bool, DirectionType> & CameraCollisionHandler::getAabbCollision(const string & aabbId) const
{
	return _aabbCollisions.at(aabbId);
}

const string & CameraCollisionHandler::getTerrainId() const
{
	return _terrainId;
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