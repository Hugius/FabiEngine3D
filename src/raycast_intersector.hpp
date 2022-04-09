#pragma once

#include "raycast_calculator.hpp"
#include "terrain_entity_manager.hpp"
#include "aabb_entity_manager.hpp"
#include "box.hpp"

class RaycastIntersector final
{
public:
	void update();
	void inject(shared_ptr<RaycastCalculator> raycastCalculator);
	void inject(shared_ptr<TerrainEntityManager> terrainManager);
	void inject(shared_ptr<AabbEntityManager> aabbManager);
	void setTerrainIntersectionEnabled(bool value);
	void setTerrainIntersectionDistance(float distance);
	void setTerrainIntersectionPrecision(float precision);
	void setAabbIntersectionEnabled(bool value);
	void resetTerrainStatus(const string & terrainId);
	void resetAabbStatus(const string & aabbId);

	const string & getTerrainId() const;
	const string & getClosestAabbId() const;

	const fvec3 & getPointOnTerrain() const;

	const float getTerrainIntersectionDistance() const;
	const float getTerrainIntersectionPrecision() const;
	const float getDistanceToTerrain() const;
	const float getDistanceToAabb(const string & id) const;

	const bool isTerrainIntersectionEnabled() const;
	const bool isAabbIntersectionEnabled() const;

private:
	const fvec3 _calculatePointOnTerrain() const;

	const float _calculateDistanceToTerrain() const;
	const float _calculateDistanceToAabb(shared_ptr<AabbEntity> entity) const;
	const float _calculateRayBoxIntersectionDistance(const shared_ptr<Ray> ray, const shared_ptr<Box> box) const;

	const bool _isUnderTerrain(float distance) const;

	unordered_map<string, float> _aabbIntersections = {};

	shared_ptr<RaycastCalculator> _raycastCalculator = nullptr;
	shared_ptr<TerrainEntityManager> _terrainManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbManager = nullptr;

	string _terrainId = "";
	string _closestAabbId = "";

	fvec3 _pointOnTerrain = fvec3(0.0f);

	float _terrainIntersectionDistance = 0.0f;
	float _terrainIntersectionPrecision = 0.0f;
	float _distanceToTerrain = 0.0f;

	bool _isTerrainIntersectionEnabled = false;
	bool _isAabbIntersectionEnabled = false;
};