#pragma once

#include "terrain_entity_manager.hpp"
#include "ray.hpp"
#include "box.hpp"
#include "camera.hpp"

class Raycaster final
{
public:
	void inject(shared_ptr<TerrainEntityManager> terrainManager);
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void update(const ivec2& cursorPosition);
	void setTerrainPointingEnabled(bool value);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	const float getTerrainPointingDistance() const;
	const float getTerrainPointingPrecision() const;
	const float calculateRayBoxIntersectionDistance(const Ray& ray, const Box& box) const;

	const fvec3& getTerrainPoint() const;
	const fvec3 calculatePointOnRay(const Ray& ray, float distance) const;

	const bool isTerrainPointingEnabled() const;

	const Ray& getCursorRay() const;

private:
	const fvec4 _convertToViewSpace(const fvec4& clipCoords) const;

	const fvec3 _convertToWorldSpace(const fvec4& viewCoords) const;
	const fvec3 _calculateTerrainPoint() const;

	const bool _isUnderTerrain(float distance) const;

	const Ray _calculateCursorRay(const ivec2& cursorPosition) const;

	fvec3 _terrainPoint = fvec3(0.0f);

	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;

	bool _isTerrainPointingEnabled = false;

	Ray _cursorRay = Ray(fvec3(0.0f), fvec3(0.0f));

	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<TerrainEntityManager> _terrainManager = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};