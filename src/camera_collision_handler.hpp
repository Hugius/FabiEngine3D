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
	void _handleTerrainCollision();

	const bool _handleAabbCollision(DirectionType direction) const;
	const bool _isInsideAabb(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const shared_ptr<Box> box) const;
	const bool _isInsideAabbX(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const;
	const bool _isInsideAabbY(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const;
	const bool _isInsideAabbZ(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const;

	shared_ptr<Box> _cameraBox = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;

	fvec3 _lastCameraPosition = fvec3(0.0f);

	float _cameraTerrainResponseHeight = 0.0f;
	float _cameraTerrainResponseSpeed = 0.0f;

	bool _isCameraAabbResponseEnabledX = false;
	bool _isCameraAabbResponseEnabledY = false;
	bool _isCameraAabbResponseEnabledZ = false;
	bool _isCameraTerrainResponseEnabled = false;
	bool _isCameraUnderTerrain = false;

	DirectionOrderType _responseDirectionOrder = DirectionOrderType::XYZ;
};