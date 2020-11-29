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
	void enableAabbResponse();
	void disableAabbResponse();
	void enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableTerrainResponse();

	bool isCameraAboveGround();
	bool isCameraUnderGround();

private:
	CollisionDetector& _collisionDetector;

	float _cameraHeight = 0.0f;
	float _cameraSpeed = 0.0f;

	bool _aabbResponseEnabled    = false;
	bool _terrainResponseEnabled = false;
	bool _aboveGround			 = false;
	bool _underGround			 = false;
};