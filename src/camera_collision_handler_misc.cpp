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

const pair<bool, DirectionType> & CameraCollisionHandler::getAabbCollision(const string & aabbId) const
{
	return _aabbCollisions.at(aabbId);
}

const bool CameraCollisionHandler::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}