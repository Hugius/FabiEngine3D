#pragma once

#include "raycast_calculator.hpp"
#include "terrain_manager.hpp"
#include "aabb_manager.hpp"
#include "box.hpp"

class RaycastIntersector final
{
public:
	RaycastIntersector();

	void inject(shared_ptr<RaycastCalculator> raycastCalculator);
	void inject(shared_ptr<TerrainManager> terrainManager);
	void inject(shared_ptr<AabbManager> aabbManager);
	void calculateTerrainIntersection(float maxDistance, float precision);
	void calculateAabbsIntersection();
	void clearTerrainIntersection();
	void clearAabbsIntersection();

	const vector<string> getAabbIds() const;

	const string & getClosestAabbId() const;

	const fvec3 & getPointOnTerrain() const;

	const float getDistanceToTerrain() const;
	const float getDistanceToAabb(const string & aabbId) const;

private:
	const fvec3 _getPointOnTerrain(float distance, float precision) const;

	const float _getDistanceToTerrain() const;
	const float _getDistanceToAabb(shared_ptr<Aabb> aabb) const;
	const float _getDistanceBetweenRayAndBox(shared_ptr<Ray> ray, shared_ptr<Box> box) const;

	const bool _isInsideTerrain(float distance) const;

	unordered_map<string, float> _aabbIntersections = {};

	shared_ptr<RaycastCalculator> _raycastCalculator = nullptr;
	shared_ptr<TerrainManager> _terrainManager = nullptr;
	shared_ptr<AabbManager> _aabbManager = nullptr;

	string _closestAabbId = "";

	fvec3 _pointOnTerrain = fvec3(0.0f);

	float _distanceToTerrain = 0.0f;
};