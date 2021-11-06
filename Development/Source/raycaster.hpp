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
	float getTerrainPointingDistance();
	float getTerrainPointingPrecision();
	float calculateRayBoxIntersectionDistance(Ray ray, Box box);

	// Vectors
	Ray getCursorRay();
	Vec3 getTerrainPoint();
	Vec3 getPointOnRay(Ray ray, float distance);

	// Booleans
	bool isTerrainPointingEnabled();

private:
	// Vectors
	Vec4 _convertToViewSpace(Vec4 clipCoords);
	Vec3 _convertToWorldSpace(Vec4 viewCoords);
	Vec3 _calculateTerrainPoint();

	// Booleans
	bool _isUnderTerrain(float distance);

	// Miscellaneous
	Ray _calculateCursorRay(Ivec2 cursorPosition);

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