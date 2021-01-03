#pragma once

#include "terrain_entity_manager.hpp"

class MousePicker final
{
public:
	MousePicker(RenderBus& renderBus);
	~MousePicker() = default;

	void update(Ivec2 mousePos, TerrainEntityManager& terrainManager);

	float checkCursorInBox(Vec3 lb, Vec3 rt, Vec3 cameraPos);

	Vec3 getRay();
	Vec3 getTerrainPoint();

	bool isValidTerrainPoint();

private:
	RenderBus& _renderBus;

	Vec3 _getMouseRay(Ivec2 mousePos);
	Vec2 _converToNDC(Ivec2 val);
	Vec4 _convertToViewSpace(Vec4 value);
	Vec3 _convertToWorldSpace(Vec4 value);
	Vec3 _getPointOnRay(Vec3 ray, float distance);
	Vec3 _binarySearch(int count, float start, float finish, Vec3 ray, TerrainEntityManager& terrainManager);
	bool _notUnderTerrain(float start, float finish, Vec3 ray, TerrainEntityManager& terrainManager);

	Vec3 _ray = Vec3(0.0f);
	Vec3 _terrainPoint = Vec3(0.0f);

	bool _isValidTerrainPoint = false;
};