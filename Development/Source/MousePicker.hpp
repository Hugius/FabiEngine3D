#pragma once

#include <GLM/glm.hpp>

using glm::ivec2;
using glm::vec3;
using glm::vec4;

#include "TerrainEntityManager.hpp"

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
	ShaderBus& p_shaderBus;

	vec3 p_getMouseRay(ivec2 mousePos);
	vec2 p_converToNDC(ivec2 val);
	vec4 p_convertToViewSpace(vec4 val);
	vec3 p_convertToWorldSpace(vec4 val);
	vec3 p_getPointOnRay(vec3 ray, float distance);
	vec3 p_binarySearch(int count, float start, float finish, vec3 ray, TerrainEntityManager& terrainManager);
	bool p_notUnderTerrain(float start, float finish, vec3 ray, TerrainEntityManager& terrainManager);

	vec3 p_ray;
	vec3 p_terrainPoint;
};