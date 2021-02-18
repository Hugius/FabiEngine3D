#pragma once

#include "terrain_entity_manager.hpp"

class RayCaster final
{
public:
	RayCaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);
	~RayCaster() = default;

	void update(Ivec2 mousePos);

	float checkCursorInBox(Vec3 lb, Vec3 rt, Vec3 cameraPos);

	Vec3 getRay();
	Vec3 getTerrainPoint();

private:
	RenderBus& _renderBus;

	Vec3 _getMouseRay(Ivec2 mousePos);
	Vec2 _converToNDC(Ivec2 val);
	Vec4 _convertToViewSpace(Vec4 value);
	Vec3 _convertToWorldSpace(Vec4 value);
	Vec3 _getPointOnRay(float distance);
	Vec3 _calculateTerrainPoint(float maxDistance);

	bool _isUnderTerrain(float distance);

	Vec3 _ray = Vec3(0.0f);
	Vec3 _terrainPoint = Vec3(0.0f);

	TerrainEntityManager& _terrainManager;
};