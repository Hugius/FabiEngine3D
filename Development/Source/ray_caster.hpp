#pragma once

#include "terrain_entity_manager.hpp"

class RayCaster final
{
public:
	RayCaster(RenderBus& renderBus, TerrainEntityManager& terrainManager);

	// Voids
	void update(Ivec2 cursorPosition);
	void setTerrainPointingEnabled(bool enabled);
	void setTerrainPointingDistance(float distance);
	void setTerrainPointingPrecision(float precision);

	// Floats
	float getTerrainPointingDistance();
	float getTerrainPointingPrecision();
	float checkCursorInBox(Vec3 leftBottomCoordinate, Vec3 rightTopCoordinate, Vec3 cameraPosition);

	// Vectors
	Vec3 getRay();
	Vec3 getTerrainPoint();

	// Booleans
	bool isTerrainPointingEnabled();

private:
	RenderBus& _renderBus;

	Vec3 _getCursorRay(Ivec2 cursorPosition);
	Vec2 _converToNDC(Ivec2 val);
	Vec4 _convertToViewSpace(Vec4 value);
	Vec3 _convertToWorldSpace(Vec4 value);
	Vec3 _getPointOnRay(float distance);
	Vec3 _calculateTerrainPoint();

	bool _isUnderTerrain(float distance);

	Vec3 _cursorRay = Vec3(0.0f);
	Vec3 _terrainPoint = Vec3(0.0f);

	TerrainEntityManager& _terrainManager;

	bool _isTerrainPointingEnabled = false;

	float _terrainPointingDistance = 0.0f;
	float _terrainPointingPrecision = 0.0f;
};