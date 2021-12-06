#pragma once

#include "terrain_entity_manager.hpp"
#include "ray.hpp"
#include "box.hpp"

class Raycaster final
{
public:
	Raycaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);

	// VOID
	void update(ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool value);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	// FLOAT
	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float calculateRayBoxIntersectionDistance(Ray ray, Box box) const;

	// FVEC3
	const fvec3 getTerrainPoint() const;
	const fvec3 getPointOnRay(Ray ray, float distance) const;

	// BOOL
	const bool isTerrainPointingEnabled() const;

	// MISCELLANEOUS
	const Ray getCursorRay() const;

private:
	// FVEC4
	const fvec4 _convertToViewSpace(fvec4 clipCoords) const;

	// FVEC3
	const fvec3 _convertToWorldSpace(fvec4 viewCoords) const;
	const fvec3 _calculateTerrainPoint() const;

	// BOOL
	const bool _isUnderTerrain(float distance) const;

	// MISCELLANEOUS
	const Ray _calculateCursorRay(ivec2 cursorPosition) const;

	// FVEC3
	fvec3 _terrainPoint = fvec3(0.0f);

	// FLOAT
	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;

	// BOOL
	bool _isTerrainPointingEnabled = false;

	// MISCELLANEOUS
	RenderBus& _renderBus;
	TerrainEntityManager& _terrainManager;
	Ray _cursorRay = Ray(fvec3(0.0f), fvec3(0.0f));
};