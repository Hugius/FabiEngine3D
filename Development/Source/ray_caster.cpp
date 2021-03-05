#include "ray_caster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "logger.hpp"

#include <algorithm>

RayCaster::RayCaster(RenderBus& renderBus, TerrainEntityManager& terrainManager) :
	_renderBus(renderBus),
	_terrainManager(terrainManager)
{

}

void RayCaster::update(Ivec2 cursorPosition)
{
	// Update raycasting
	Vec3 mouseRay = _getMouseRay(cursorPosition);
	_ray = mouseRay;

	// Update cursor positioning on terrain
	if (_isTerrainPointingEnabled)
	{
		if (_terrainManager.getSelectedTerrain() != nullptr)
		{
			_terrainPoint = _calculateTerrainPoint();
		}
		else
		{
			_terrainPoint = Vec3(-1.0f);
		}
	}
	else
	{
		_terrainPoint = Vec3(-1.0f);
	}
}

void RayCaster::setTerrainPointingEnabled(bool enabled)
{
	_isTerrainPointingEnabled = enabled;
}

void RayCaster::setTerrainPointingDistance(float distance)
{
	_terrainPointingDistance = distance;
}

void RayCaster::setTerrainPointingPrecision(float precision)
{
	_terrainPointingPrecision = precision;
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

Vec3 RayCaster::_getMouseRay(Ivec2 cursorPosition)
{
	Vec2 NDC = _converToNDC(cursorPosition);
	Vec4 clipCoords = Vec4(NDC.x, NDC.y, -1.0f, 1.0f);
	Vec4 viewCoords = _convertToViewSpace(clipCoords);
	Vec3 worldCoords = _convertToWorldSpace(viewCoords);

	return worldCoords;
}

Vec2 RayCaster::_converToNDC(Ivec2 val)
{
	float x = ((2.0f * val.x) / Config::getInst().getWindowSize().x) - 1.0f;
	float y = ((2.0f * val.y) / Config::getInst().getWindowSize().y) - 1.0f;

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

bool RayCaster::_isUnderTerrain(float distance)
{
	// Scale ray
	Vec3 scaledRay = _getPointOnRay(distance);

	// Retrieve height
	auto selectedTerrain = _terrainManager.getSelectedTerrain();
	float terrainHeight = _terrainManager.getPixelHeight(
		selectedTerrain->getID(),
		scaledRay.x + (selectedTerrain->getSize() / 2.0f), 
		scaledRay.z + (selectedTerrain->getSize() / 2.0f));

	// Return
	return (scaledRay.y < terrainHeight);
}

Vec3 RayCaster::_calculateTerrainPoint()
{
	// Temporary values
	float distance = 0.0f;

	// Try to find point on terrain
	while (distance < _terrainPointingDistance)
	{
		// Intersected with terrain
		if (_isUnderTerrain(distance))
		{
			// Calculate point on terrain
			Vec3 endPoint = _getPointOnRay(distance - (_terrainPointingPrecision / 2.0f));

			// Check if selected point is inside the terrain size
			auto selectedTerrain = _terrainManager.getSelectedTerrain();
			if (_terrainManager.isInside(
				selectedTerrain->getID(),
				endPoint.x + (selectedTerrain->getSize() / 2.0f),
				endPoint.z + (selectedTerrain->getSize() / 2.0f)))
			{
				return endPoint;
			}
			else
			{
				break;
			}
		}
		else
		{
			distance += _terrainPointingPrecision;
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