#pragma once

#include "collision_detector.hpp"
#include "aabb_entity.hpp"
#include "camera.hpp"
#include "terrain_entity_manager.hpp"

class CollisionResolver final
{
public:
	// Voids
	void update(const unordered_map<string, shared_ptr<AabbEntity>>& boxes, TerrainEntityManager& terrainManager, Camera& camera, CollisionDetector& collisionDetector);
	void setCameraBoxSize(float bottom, float top, float left, float right, float front, float back);
	void enableCameraAabbResponse(bool x, bool y, bool z);
	void disableCameraAabbResponse();
	void enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableCameraTerrainResponse();

	// Booleans
	bool isCameraUnderTerrain();
	bool isCameraAabbResponseEnabled();
	bool isCameraTerrainResponseEnabled();

private:
	// Floats
	float _cameraAabbBottom = 0.0f;
	float _cameraAabbTop = 0.0f;
	float _cameraAabbLeft = 0.0f;
	float _cameraAabbRight = 0.0f;
	float _cameraAabbFront = 0.0f;
	float _cameraAabbBack = 0.0f;
	float _cameraTerrainHeight = 0.0f;
	float _cameraTerrainSpeed = 0.0f;

	// Booleans
	bool _isCameraAabbResponseEnabled = false;
	bool _isCameraAabbResponseEnabledX = false;
	bool _isCameraAabbResponseEnabledY = false;
	bool _isCameraAabbResponseEnabledZ = false;
	bool _isCameraTerrainResponseEnabled = false;
	bool _isCameraUnderTerrain = false;
};