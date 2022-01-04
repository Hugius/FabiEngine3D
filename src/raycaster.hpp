#pragma once

#include "terrain_entity_manager.hpp"
#include "ray.hpp"
#include "box.hpp"

class Raycaster final
{
public:
	void update(TerrainEntityManager& terrainManager, RenderBus& renderBus, ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool value);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float calculateRayBoxIntersectionDistance(Ray ray, Box box) const;

	const fvec3 getTerrainPoint() const;
	const fvec3 getPointOnRay(Ray ray, float distance) const;

	const bool isTerrainPointingEnabled() const;

	const Ray getCursorRay() const;

private:
	const fvec4 _convertToViewSpace(RenderBus& renderBus, fvec4 clipCoords) const;

	const fvec3 _convertToWorldSpace(RenderBus& renderBus, fvec4 viewCoords) const;
	const fvec3 _calculateTerrainPoint(TerrainEntityManager& terrainManager) const;

	const bool _isUnderTerrain(TerrainEntityManager& terrainManager, float distance) const;

	const Ray _calculateCursorRay(RenderBus& renderBus, ivec2 cursorPosition) const;

	fvec3 _terrainPoint = fvec3(0.0f);

	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;

	bool _isTerrainPointingEnabled = false;

	Ray _cursorRay = Ray(fvec3(0.0f), fvec3(0.0f));
};