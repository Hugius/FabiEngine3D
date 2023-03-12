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
	void setCameraBox(shared_ptr<Box> value);
	void calculateCollisionWithTerrain(bool mustRespondY, float responseSpeed);
	void calculateCollisionWithAabbs(bool mustRespondX, bool mustRespondY, bool mustRespondZ);
	void clearCollisionWithTerrain();
	void clearCollisionWithAabbs();

	const vector<pair<string, DirectionType>> & getAabbIdsThatCollided() const;

	const bool hasCollidedWithTerrain() const;

private:
	void _calculateCollisionWithTerrain(bool mustRespondY, float responseSpeed);

	const bool _hasCollidedWithAabbs(DirectionType direction, bool mustRespondX, bool mustRespondY, bool mustRespondZ);
	const bool _isInsideAabb(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbX(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbY(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;
	const bool _isInsideAabbZ(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, shared_ptr<Box> cameraBox) const;

	vector<pair<string, DirectionType>> _aabbCollisions = {};

	shared_ptr<Box> _cameraBox = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;

	fvec3 _lastCameraPosition = fvec3(0.0f);

	bool _hasCollidedWithTerrain = false;

	DirectionOrderType _aabbResponseDirectionOrder = DirectionOrderType::XYZ;
};