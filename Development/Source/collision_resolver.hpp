#pragma once

#include "collision_detector.hpp"
#include "aabb_entity.hpp"
#include "camera_manager.hpp"
#include "terrain_entity_manager.hpp"

class CollisionResolver
{
public:
	CollisionResolver(CollisionDetector& collisionDetector);
	virtual ~CollisionResolver() = default;
	
	void update(const unordered_map<string, shared_ptr<AabbEntity>>& boxes, TerrainEntityManager& terrainManager, CameraManager & camera);
	void enableAabbResponse(float bottom, float top, float left, float right, float front, float back);
	void disableAabbResponse();
	void enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableTerrainResponse();

	bool isCameraUnderTerrain();

private:
	CollisionDetector& _collisionDetector;

	float _cameraAabbBottom = 0.0f;
	float _cameraAabbTop = 0.0f;
	float _cameraAabbLeft = 0.0f;
	float _cameraAabbRight = 0.0f;
	float _cameraAabbFront = 0.0f;
	float _cameraAabbBack = 0.0f;
	float _cameraTerrainHeight = 0.0f;
	float _cameraTerrainSpeed = 0.0f;

	bool _aabbResponseEnabled    = false;
	bool _terrainResponseEnabled = false;
	bool _isCameraUnderTerrain	 = false;
};