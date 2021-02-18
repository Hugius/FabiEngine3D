#include "ray_caster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

RayCaster::RayCaster(RenderBus& renderBus) :
	_renderBus(renderBus)
{

}

void RayCaster::update(Ivec2 mousePos, TerrainEntityManager& terrainManager)
{
	// Simple raycasting
	Vec3 mouseRay = _getMouseRay(Ivec2(mousePos.x, Config::getInst().getWindowHeight() - mousePos.y));
	_ray = mouseRay;

	// Check if a terrain is selected
	if (terrainManager.getSelectedTerrain() != nullptr)
	{
		_terrainPoint = _calculateTerrainPoint(terrainManager.getSelectedTerrain()->getSize() * 2.0f, terrainManager);
	}
	else
	{
		_terrainPoint = Vec3(-1.0f);
	}
}

float RayCaster::checkCursorInBox(Vec3 lb, Vec3 rt, Vec3 cameraPos) // From some stackoverflow post I forgot
{
	// Direction fraction
	Vec3 dirfrac;
	dirfrac.x = 1.0f / _ray.x;
	dirfrac.y = 1.0f / _ray.y;
	dirfrac.z = 1.0f / _ray.z;

	// Define AABB
	float t1 = (lb.x - cameraPos.x) * dirfrac.x;
	float t2 = (rt.x - cameraPos.x) * dirfrac.x;
	float t3 = (lb.y - cameraPos.y) * dirfrac.y;
	float t4 = (rt.y - cameraPos.y) * dirfrac.y;
	float t5 = (lb.z - cameraPos.z) * dirfrac.z;
	float t6 = (rt.z - cameraPos.z) * dirfrac.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// AABB is behind
	if (tmax < 0)
	{
		return -1.0f;
	}

	// No intersection
	if (tmin > tmax)
	{
		return -1.0f;
	}
	
	// Intersection
	return tmin;
}

Vec3 RayCaster::_getMouseRay(Ivec2 mousePos)
{
	Vec2 NDC = _converToNDC(mousePos);
	Vec4 clipCoords = Vec4(NDC.x, NDC.y, -1.0f, 1.0f);
	Vec4 viewCoords = _convertToViewSpace(clipCoords);
	Vec3 worldCoords = _convertToWorldSpace(viewCoords);

	return worldCoords;
}

Vec2 RayCaster::_converToNDC(Ivec2 val)
{
	float x = ((2.0f * val.x) / Config::getInst().getWindowWidth ()) - 1.0f;
	float y = ((2.0f * val.y) / Config::getInst().getWindowHeight()) - 1.0f;

	return Vec2(x, y);
}

Vec4 RayCaster::_convertToViewSpace(Vec4 value)
{
	Matrix44 invertedProjection = _renderBus.getProjectionMatrix();
	invertedProjection.invert();
	Vec4 viewCoords = invertedProjection * value;

	return Vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

Vec3 RayCaster::_convertToWorldSpace(Vec4 value)
{
	Matrix44 invertedView = _renderBus.getViewMatrix();
	invertedView.invert();
	Vec4 worldCoords = invertedView * value;
	worldCoords.normalize();

	return Vec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

Vec3 RayCaster::_getPointOnRay(float distance)
{
	Vec3 cameraPos = _renderBus.getCameraPosition();
	Vec3 scaledRay = _ray * distance;

	return cameraPos + scaledRay;
}

bool RayCaster::_isUnderTerrain(float start, float end, TerrainEntityManager& terrainManager)
{
	Vec3 startPoint = _getPointOnRay(start);
	Vec3 endPoint   = _getPointOnRay(end);

	float startHeight = terrainManager.getPixelHeight(
		terrainManager.getSelectedTerrain()->getID(),
		startPoint.x + terrainManager.getSelectedTerrain()->getSize() / 2.0f, 
		startPoint.z + terrainManager.getSelectedTerrain()->getSize() / 2.0f);

	float endHeight = terrainManager.getPixelHeight(
		terrainManager.getSelectedTerrain()->getID(),
		endPoint.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f), 
		endPoint.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f));

	return (startPoint.y > startHeight && endPoint.y < endHeight);
}

Vec3 RayCaster::_calculateTerrainPoint(float maxDistance, TerrainEntityManager& terrainManager)
{
	float total = 0.0f;

	// Try to find point on terrain
	while (total < maxDistance)
	{
		// Intersected with terrain
		if (_isUnderTerrain(0.0f, total, terrainManager))
		{
			Vec3 endPoint = _getPointOnRay(total - 0.05f);

			// Check if selected point is inside the terrain size
			if (terrainManager.isInside(
				terrainManager.getSelectedTerrain()->getID(),
				endPoint.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f),
				endPoint.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f)))
			{
				return endPoint;
			}
			else
			{
				return Vec3(-1.0f);
			}
		}
		else
		{
			total += 0.1f;
		}
	}

	return Vec3(-1.0f);
}

Vec3 RayCaster::getRay()
{
	return _ray;
}

Vec3 RayCaster::getTerrainPoint()
{
	return _terrainPoint;
}