#include "mouse_picker.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

const int   RECURSION_COUNT = 256;
const float RAY_RANGE       = 512;

MousePicker::MousePicker(RenderBus& renderBus) :
	_renderBus(renderBus)
{

}

void MousePicker::update(ivec2 mousePos, TerrainEntityManager& terrainManager)
{
	// Simple raycasting
	vec3 mouseRay = _getMouseRay(ivec2(mousePos.x, Config::getInst().getWindowHeight() - mousePos.y));
	_ray = mouseRay;

	// Check if a terrain is selected
	if (terrainManager.getSelectedTerrain() != nullptr)
	{
		// Check if looking at terrain
		if (_notUnderTerrain(0, RAY_RANGE, mouseRay, terrainManager))
		{
			_terrainPoint = _binarySearch(0, 0, RAY_RANGE, mouseRay, terrainManager);
		}
		else // Looking at sky
		{
			_terrainPoint = vec3(0.0f);
		}
	}
}

float MousePicker::checkCursorInBox(vec3 lb, vec3 rt, vec3 cameraPos)
{
	vec3 dirfrac;
	dirfrac.x = 1.0f / _ray.x;
	dirfrac.y = 1.0f / _ray.y;
	dirfrac.z = 1.0f / _ray.z;

	float t1 = (lb.x - cameraPos.x) * dirfrac.x;
	float t2 = (rt.x - cameraPos.x) * dirfrac.x;
	float t3 = (lb.y - cameraPos.y) * dirfrac.y;
	float t4 = (rt.y - cameraPos.y) * dirfrac.y;
	float t5 = (lb.z - cameraPos.z) * dirfrac.z;
	float t6 = (rt.z - cameraPos.z) * dirfrac.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return -1.0f;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return -1.0f;
	}
	
	return tmin;
}

vec3 MousePicker::_getMouseRay(ivec2 mousePos)
{
	vec2 NDC = _converToNDC(mousePos);
	vec4 clipCoords = vec4(NDC.x, NDC.y, -1.0f, 1.0f);
	vec4 viewCoords = _convertToViewSpace(clipCoords);
	vec3 worldCoords = _convertToWorldSpace(viewCoords);
	return worldCoords;
}

vec2 MousePicker::_converToNDC(ivec2 val)
{
	float x = ((2.0f * val.x) / Config::getInst().getWindowWidth ()) - 1.0f;
	float y = ((2.0f * val.y) / Config::getInst().getWindowHeight()) - 1.0f;
	return vec2(x, y);
}

vec4 MousePicker::_convertToViewSpace(vec4 val)
{
	mat4 inversedProjection = glm::inverse(_renderBus.getProjectionMatrix());
	vec4 viewCoords = inversedProjection * val;
	return vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

vec3 MousePicker::_convertToWorldSpace(vec4 val)
{
	mat4 inversedView = glm::inverse(_renderBus.getViewMatrix());
	vec4 worldCoords = inversedView * val;
	worldCoords = glm::normalize(worldCoords);
	return vec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

vec3 MousePicker::_getPointOnRay(vec3 ray, float distance)
{
	vec3 cameraPos = _renderBus.getCameraPos();
	vec3 scaledRay = vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return cameraPos + scaledRay;
}

bool MousePicker::_notUnderTerrain(float start, float finish, vec3 ray, TerrainEntityManager & terrainManager)
{
	vec3 startPoint = _getPointOnRay(ray, start);
	vec3 endPoint   = _getPointOnRay(ray, finish);

	float startHeight = terrainManager.getPixelHeight(
		terrainManager.getSelectedTerrain()->getID(),
		startPoint.x + terrainManager.getSelectedTerrain()->getSize() / 2.0f, 
		startPoint.z + terrainManager.getSelectedTerrain()->getSize() / 2.0f);

	float endHeight = terrainManager.getPixelHeight(
		terrainManager.getSelectedTerrain()->getID(),
		endPoint.x + terrainManager.getSelectedTerrain()->getSize() / 2.0f, 
		endPoint.z + terrainManager.getSelectedTerrain()->getSize() / 2.0f);
	
	return (startPoint.y > startHeight && endPoint.y < endHeight);
}

vec3 MousePicker::getRay()
{
	return _ray;
}

vec3 MousePicker::getTerrainPoint()
{
	return _terrainPoint;
}

vec3 MousePicker::_binarySearch(int count, float start, float finish, vec3 ray, TerrainEntityManager& terrainManager)
{
	// Binary search algorithm
	float half = start + ((finish - start) / 2.0f);
	if (count >= RECURSION_COUNT) 
	{
		vec3 endPoint = _getPointOnRay(ray, half);
		
		// Check if selected point is inside the terrain size
		if (terrainManager.isInside(
			terrainManager.getSelectedTerrain()->getID(),
			endPoint.x + terrainManager.getSelectedTerrain()->getSize() / 2.0f, 
			endPoint.z + terrainManager.getSelectedTerrain()->getSize() / 2.0f))
		{
			return endPoint;
		}
		else
		{
			return vec3(0.0f);
		}
	}

	// Recursion
	if (_notUnderTerrain(start, half, ray, terrainManager))
	{
		return _binarySearch(count + 1, start, half, ray, terrainManager);
	}
	else 
	{
		return _binarySearch(count + 1, half, finish, ray, terrainManager);
	}
}