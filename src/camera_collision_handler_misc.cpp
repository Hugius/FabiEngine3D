#include "camera_collision_handler.hpp"

using std::make_shared;

void CameraCollisionHandler::initialize()
{
	_cameraBox = make_shared<Box>(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	clearCollisionWithTerrain();
	clearCollisionWithAabbs();
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

const bool CameraCollisionHandler::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}

void CameraCollisionHandler::clearCollisionWithTerrain()
{
	_isCameraUnderTerrain = false;
}

void CameraCollisionHandler::clearCollisionWithAabbs()
{
	_aabbCollisions.clear();
}

const vector<pair<string, DirectionType>> & CameraCollisionHandler::getAabbCollisions() const
{
	return _aabbCollisions;
}