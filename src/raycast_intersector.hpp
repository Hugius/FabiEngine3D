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
	void setTerrainPointingEnabled(bool value);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	const string& getClosestAabbId() const;

	const fvec3& getTerrainPoint() const;

	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float getDistanceToTerrain() const;
	const float getDistanceToAabb(const string& id) const;

	const bool isTerrainPointingEnabled() const;

private:
	const fvec3 _calculateTerrainPoint() const;

	const float _calculateDistanceToTerrain() const;
	const float _calculateDistanceToAabb(shared_ptr<AabbEntity> entity) const;
	const float _calculateRayBoxIntersectionDistance(const shared_ptr<Ray> ray, const shared_ptr<Box> box) const;

	const bool _isUnderTerrain(float distance) const;

	string _closestAabbId = "";

	fvec3 _terrainPoint = fvec3(0.0f);

	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;
	float _distanceToTerrain = 0.0f;

	bool _isTerrainPointingEnabled = false;

	unordered_map<string, float> _aabbIntersections;

	shared_ptr<RaycastCalculator> _raycastCalculator = nullptr;
	shared_ptr<TerrainEntityManager> _terrainManager = nullptr;
	shared_ptr<AabbEntityManager> _aabbManager = nullptr;
};