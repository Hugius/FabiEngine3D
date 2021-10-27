#pragma once

#include "aabb_entity.hpp"
#include "camera.hpp"
#include "raycaster.hpp"
#include "collision_detector.hpp"
#include "terrain_entity_manager.hpp"
#include "box.hpp"

class CollisionResolver final
{
public:
	// Voids
	void update(const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, TerrainEntityManager& terrainManager, Camera& camera, Raycaster& raycaster, CollisionDetector& collisionDetector);
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
	// Voids
	void _handleCollision(Direction direction, shared_ptr<AabbEntity> aabb, Camera& camera, CollisionDetector& collisionDetector);

	// Vectors
	Vec3 _lastCameraPosition = Vec3(0.0f);

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
	Box _cameraBox = Box(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
};