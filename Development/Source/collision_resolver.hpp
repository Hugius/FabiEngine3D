#pragma once

#include "collision_detector.hpp"
#include "aabb_entity.hpp"
#include "camera.hpp"
#include "terrain_entity_manager.hpp"
#include "box.hpp"

class CollisionResolver final
{
public:
	CollisionResolver();

	// Voids
	void update(const unordered_map<string, shared_ptr<AabbEntity>>& boxes, TerrainEntityManager& terrainManager, Camera& camera, CollisionDetector& collisionDetector);
	void setCameraBox(const Box& box);
	void enableCameraAabbResponse(bool x, bool y, bool z);
	void disableCameraAabbResponse();
	void enableCameraTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableCameraTerrainResponse();

	// Booleans
	bool isCameraUnderTerrain();
	bool isCameraAabbResponseEnabled();
	bool isCameraTerrainResponseEnabled();

private:
	// Decimals
	float _cameraTerrainHeight = 0.0f;
	float _cameraTerrainSpeed = 0.0f;

	// Booleans
	bool _isCameraAabbResponseEnabled = false;
	bool _isCameraAabbResponseEnabledX = false;
	bool _isCameraAabbResponseEnabledY = false;
	bool _isCameraAabbResponseEnabledZ = false;
	bool _isCameraTerrainResponseEnabled = false;
	bool _isCameraUnderTerrain = false;

	// Miscellaneous
	Box _cameraBox;
};