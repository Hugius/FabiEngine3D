#pragma once

#include "terrain_entity_manager.hpp"
#include "ray.hpp"
#include "box.hpp"

class Raycaster final
{
public:
	Raycaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);

	// Voids
	void update(Ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool enabled);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	// Decimals
	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float calculateRayBoxIntersectionDistance(Ray ray, Box box) const;

	// Vectors
	const Ray getCursorRay() const;
	const Vec3 getTerrainPoint() const;
	const Vec3 getPointOnRay(Ray ray, float distance) const;

	// Booleans
	const bool isTerrainPointingEnabled() const;

private:
	// Vectors
	const Vec4 _convertToViewSpace(Vec4 clipCoords) const;
	const Vec3 _convertToWorldSpace(Vec4 viewCoords) const;
	const Vec3 _calculateTerrainPoint() const;

	// Booleans
	const bool _isUnderTerrain(float distance) const;

	// Miscellaneous
	const Ray _calculateCursorRay(Ivec2 cursorPosition) const;

	// Vectors
	Ray _cursorRay = Ray(Vec3(0.0f), Vec3(0.0f));
	Vec3 _terrainPoint = Vec3(0.0f);

	// Decimals
	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;

	// Booleans
	bool _isTerrainPointingEnabled = false;

	// Miscellaneous
	RenderBus& _renderBus;
	TerrainEntityManager& _terrainManager;
};