#pragma once

#include "camera.hpp"
#include "raycaster.hpp"
#include "camera_collision_detector.hpp"
#include "terrain_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "box.hpp"
#include "direction_order.hpp"

class CameraCollisionHandler final
{
public:
	CameraCollisionHandler();

	void inject(shared_ptr<CameraCollisionDetector> cameraCollisionDetector);
	void inject(shared_ptr<TerrainEntityManager> terrainManager);
	void inject(shared_ptr<AabbEntityManager> aabbManager);
	void inject(shared_ptr<Camera> camera);
	void update();
	void setCameraBox(const shared_ptr<Box> value);
	void setCameraAabbResponseEnabled(bool x, bool y, bool z);
	void setCameraTerrainResponseEnabled(bool value);
	void setCameraTerrainResponseHeight(float value);
	void setCameraTerrainResponseSpeed(float value);

	const float getCameraTerrainResponseHeight() const;
	const float getCameraTerrainResponseSpeed() const;

	const bool isCameraUnderTerrain() const;
	const bool isCameraAabbResponseEnabledX() const;
	const bool isCameraAabbResponseEnabledY() const;
	const bool isCameraAabbResponseEnabledZ() const;
	const bool isCameraTerrainResponseEnabled() const;

private:
	const bool _handleCollision(Direction direction) const;

	fvec3 _lastCameraPosition = fvec3(0.0f);

	float _cameraTerrainResponseHeight = 0.0f;
	float _cameraTerrainResponseSpeed = 0.0f;

	bool _isCameraAabbResponseEnabledX = false;
	bool _isCameraAabbResponseEnabledY = false;
	bool _isCameraAabbResponseEnabledZ = false;
	bool _isCameraTerrainResponseEnabled = false;
	bool _isCameraUnderTerrain = false;

	DirectionOrder _responseDirectionOrder = DirectionOrder::XYZ;
	shared_ptr<Box> _cameraBox = nullptr;

	shared_ptr<CameraCollisionDetector> _cameraCollisionDetector = nullptr;
	shared_ptr<TerrainEntityManager> _terrainManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};