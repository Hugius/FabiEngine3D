#pragma once

#include "terrain_entity_manager.hpp"

#include <GLM\\glm.hpp>

using glm::ivec2;
using glm::vec3;
using glm::vec4;

class MousePicker final
{
public:
	MousePicker(ShaderBus& shaderBus);
	~MousePicker() = default;

	void update(ivec2 mousePos, TerrainEntityManager& terrainManager);

	float checkCursorInBox(vec3 lb, vec3 rt, vec3 cameraPos);

	vec3 getRay();
	vec3 getTerrainPoint();

private:
	ShaderBus& _shaderBus;

	vec3 _getMouseRay(ivec2 mousePos);
	vec2 _converToNDC(ivec2 val);
	vec4 _convertToViewSpace(vec4 val);
	vec3 _convertToWorldSpace(vec4 val);
	vec3 _getPointOnRay(vec3 ray, float distance);
	vec3 _binarySearch(int count, float start, float finish, vec3 ray, TerrainEntityManager& terrainManager);
	bool _notUnderTerrain(float start, float finish, vec3 ray, TerrainEntityManager& terrainManager);

	vec3 _ray;
	vec3 _terrainPoint;
};