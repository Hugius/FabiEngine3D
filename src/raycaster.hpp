#pragma once

#include "terrain_entity_manager.hpp"
#include "ray.hpp"
#include "box.hpp"

class Raycaster final
{
public:
	Raycaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);

	// Voids
	void update(ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool enabled);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	// Decimals
	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float calculateRayBoxIntersectionDistance(Ray ray, Box box) const;

	// Vectors
	const Ray getCursorRay() const;
	const fvec3 getTerrainPoint() const;
	const fvec3 getPointOnRay(Ray ray, float distance) const;

	// Booleans
	const bool isTerrainPointingEnabled() const;

private:
	// Vectors
	const fvec4 _convertToViewSpace(fvec4 clipCoords) const;
	const fvec3 _convertToWorldSpace(fvec4 viewCoords) const;
	const fvec3 _calculateTerrainPoint() const;

	// Booleans
	const bool _isUnderTerrain(float distance) const;

	// Miscellaneous
	const Ray _calculateCursorRay(ivec2 cursorPosition) const;

	// Vectors
	Ray _cursorRay = Ray(fvec3(0.0f), fvec3(0.0f));
	fvec3 _terrainPoint = fvec3(0.0f);

	// Decimals
	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;

	// Booleans
	bool _isTerrainPointingEnabled = false;

	// Miscellaneous
	RenderBus& _renderBus;
	TerrainEntityManager& _terrainManager;
};