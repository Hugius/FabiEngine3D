#include "mouse_picker.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>
#include <GLM/glm.hpp>

const int   RECURSION_COUNT = 256;
const float RAY_RANGE       = 512;

MousePicker::MousePicker(RenderBus& renderBus) :
	_renderBus(renderBus)
{

}

void MousePicker::update(Ivec2 mousePos, TerrainEntityManager& terrainManager)
{
	// Simple raycasting
	Vec3 mouseRay = _getMouseRay(Ivec2(mousePos.x, Config::getInst().getWindowHeight() - mousePos.y));
	_ray = mouseRay;

	// Check if a terrain is selected
	if (terrainManager.getSelectedTerrain() != nullptr)
	{
		// Check if looking at terrain
		if (_notUnderTerrain(0, RAY_RANGE, mouseRay, terrainManager))
		{
			_terrainPoint = _binarySearch(0, 0, RAY_RANGE, mouseRay, terrainManager);
			_isValidTerrainPoint = true;
		}
		else // Looking at sky
		{
			_terrainPoint = Vec3(0.0f);
			_isValidTerrainPoint = false;
		}
	}
	else
	{
		_isValidTerrainPoint = false;
	}
}

float MousePicker::checkCursorInBox(Vec3 lb, Vec3 rt, Vec3 cameraPos)
{
	Vec3 dirfrac;
	dirfrac.x = 1.0f / _ray.x;
	dirfrac.y = 1.0f / _ray.y;
	dirfrac.z = 1.0f / _ray.z;

	float t1 = (lb.x - cameraPos.x) * dirfrac.x;
	float t2 = (rt.x - cameraPos.x) * dirfrac.x;
	float t3 = (lb.y - cameraPos.y) * dirfrac.y;
	float t4 = (rt.y - cameraPos.y) * dirfrac.y;
	float t5 = (lb.z - cameraPos.z) * dirfrac.z;
	float t6 = (rt.z - cameraPos.z) * dirfrac.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

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

Vec3 MousePicker::_getMouseRay(Ivec2 mousePos)
{
	Vec2 NDC = _converToNDC(mousePos);
	Vec4 clipCoords = Vec4(NDC.x, NDC.y, -1.0f, 1.0f);
	Vec4 viewCoords = _convertToViewSpace(clipCoords);
	Vec3 worldCoords = _convertToWorldSpace(viewCoords);
	return worldCoords;
}

Vec2 MousePicker::_converToNDC(Ivec2 val)
{
	float x = ((2.0f * val.x) / Config::getInst().getWindowWidth ()) - 1.0f;
	float y = ((2.0f * val.y) / Config::getInst().getWindowHeight()) - 1.0f;
	return Vec2(x, y);
}

Vec4 MousePicker::_convertToViewSpace(Vec4 val)
{
	Matrix44 invertedProjection = _renderBus.getProjectionMatrix();
	invertedProjection.invert();
	Vec4 viewCoords = invertedProjection * val;
	return Vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

Vec3 MousePicker::_convertToWorldSpace(Vec4 val)
{
	Matrix44 invertedView = _renderBus.getViewMatrix();
	invertedView.invert();
	Vec4 worldCoords = invertedView * val;
	worldCoords.normalize();
	return Vec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

Vec3 MousePicker::_getPointOnRay(Vec3 ray, float distance)
{
	Vec3 cameraPos = _renderBus.getCameraPosition();
	Vec3 scaledRay = Vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return cameraPos + scaledRay;
}

bool MousePicker::_notUnderTerrain(float start, float finish, Vec3 ray, TerrainEntityManager & terrainManager)
{
	Vec3 startPoint = _getPointOnRay(ray, start);
	Vec3 endPoint   = _getPointOnRay(ray, finish);

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

Vec3 MousePicker::getRay()
{
	return _ray;
}

Vec3 MousePicker::getTerrainPoint()
{
	return _terrainPoint;
}

bool MousePicker::isValidTerrainPoint()
{
	return _isValidTerrainPoint;
}

Vec3 MousePicker::_binarySearch(int count, float start, float finish, Vec3 ray, TerrainEntityManager& terrainManager)
{
	// Binary search algorithm
	float half = start + ((finish - start) / 2.0f);
	if (count >= RECURSION_COUNT) 
	{
		Vec3 endPoint = _getPointOnRay(ray, half);
		
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
			return Vec3(0.0f);
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