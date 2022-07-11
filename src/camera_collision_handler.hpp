#pragma once

#include "camera.hpp"
#include "terrain_manager.hpp"
#include "aabb_manager.hpp"
#include "box.hpp"
#include "direction_order_type.hpp"

class CameraCollisionHandler final
{
public:
	CameraCollisionHandler();

	void inject(shared_ptr<TerrainManager> terrainManager);
	void inject(shared_ptr<AabbManager> aabbManager);
	void inject(shared_ptr<Camera> camera);
	void calculateTerrainCollision(bool mustRespondY);
	void calculateAabbCollision(bool mustRespondX, bool mustRespondY, bool mustRespondZ);
	void setCameraBox(shared_ptr<Box> value);
	void setCameraTerrainResponseHeight(float value);
	void setCameraTerrainResponseSpeed(float value);
	void resetTerrainStatus(const string & terrainId);
	void resetAabbStatus(const string & aabbId);

	const pair<bool, DirectionType> & getAabbCollision(const string & aabbId) const;

	const string & getTerrainId() const;

	const float getCameraTerrainResponseHeight() const;
	const float getCameraTerrainResponseSpeed() const;

	const bool isCameraUnderTerrain() const;

private:
	const bool _calculateAabbCollision(DirectionType direction, bool mustRespondX, bool mustRespondY, bool mustRespondZ);
	const bool _isInsideAabb(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbX(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbY(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbZ(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;

	unordered_map<string, pair<bool, DirectionType>> _aabbCollisions = {};

	shared_ptr<Box> _cameraBox = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;

	string _terrainId = "";

	fvec3 _lastCameraPosition = fvec3(0.0f);

	float _cameraTerrainResponseHeight = 0.0f;
	float _cameraTerrainResponseSpeed = 0.0f;

	bool _isCameraUnderTerrain = false;

	DirectionOrderType _responseDirectionOrder = DirectionOrderType::XYZ;
};