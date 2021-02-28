#pragma once

#include "terrain_entity_manager.hpp"

class RayCaster final
{
public:
	RayCaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);
	~RayCaster() = default;

	void update(Ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool enabled);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	float checkCursorInBox(Vec3 lb, Vec3 rt, Vec3 cameraPos);

	Vec3 getRay();
	Vec3 getTerrainPoint();

private:
	RenderBus& _renderBus;

	Vec3 _getMouseRay(Ivec2 cursorPosition);
	Vec2 _converToNDC(Ivec2 val);
	Vec4 _convertToViewSpace(Vec4 value);
	Vec3 _convertToWorldSpace(Vec4 value);
	Vec3 _getPointOnRay(float distance);
	Vec3 _calculateTerrainPoint();

	bool _isUnderTerrain(float distance);

	Vec3 _ray = Vec3(0.0f);
	Vec3 _terrainPoint = Vec3(0.0f);

	TerrainEntityManager& _terrainManager;

	bool _isTerrainPointingEnabled = false;

	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;
};