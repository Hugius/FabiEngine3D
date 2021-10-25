#include "raycaster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "tools.hpp"

#include <algorithm>

using std::min;
using std::max;

Raycaster::Raycaster(RenderBus& renderBus, TerrainEntityManager& terrainManager)
	:
	_renderBus(renderBus),
	_terrainManager(terrainManager)
{

}

void Raycaster::update(Ivec2 cursorPosition)
{
	// Update raycasting
	_cursorRay = _calculateCursorRay(cursorPosition);

	// Update cursor pointing on terrain
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

void Raycaster::setTerrainPointingEnabled(bool enabled)
{
	_isTerrainPointingEnabled = enabled;
}

void Raycaster::setTerrainPointingDistance(float distance)
{
	_terrainPointingDistance = distance;
}

void Raycaster::setTerrainPointingPrecision(float precision)
{
	_terrainPointingPrecision = precision;
}

bool Raycaster::isTerrainPointingEnabled()
{
	return _isTerrainPointingEnabled;
}

float Raycaster::getTerrainPointingDistance()
{
	return _terrainPointingDistance;
}

float Raycaster::getTerrainPointingPrecision()
{
	return _terrainPointingPrecision;
}

Ray Raycaster::getCursorRay()
{
	return _cursorRay;
}

Vec3 Raycaster::getTerrainPoint()
{
	return _terrainPoint;
}

// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
float Raycaster::checkRayBoxIntersection(Ray ray, Box box)
{
	// Ray direction
	Vec3 normalizedRayDirection;
	normalizedRayDirection.x = (1.0f / ray.getDirection().x);
	normalizedRayDirection.y = (1.0f / ray.getDirection().y);
	normalizedRayDirection.z = (1.0f / ray.getDirection().z);

	// Calculates distances between camera & collision
	float distance1 = ((box.getLeft() - ray.getPosition().x) * normalizedRayDirection.x);
	float distance2 = ((box.getRight() - ray.getPosition().x) * normalizedRayDirection.x);
	float distance3 = ((box.getBottom() - ray.getPosition().y) * normalizedRayDirection.y);
	float distance4 = ((box.getTop() - ray.getPosition().y) * normalizedRayDirection.y);
	float distance5 = ((box.getFront() - ray.getPosition().z) * normalizedRayDirection.z);
	float distance6 = ((box.getBack() - ray.getPosition().z) * normalizedRayDirection.z);
	float minDistance = max(max(min(distance1, distance2), min(distance3, distance4)), min(distance5, distance6));
	float maxDistance = min(min(max(distance1, distance2), max(distance3, distance4)), max(distance5, distance6));

	// AABB is behind camera
	if (maxDistance < 0.0f)
	{
		return -1.0f;
	}

	// No intersection
	if (minDistance > maxDistance)
	{
		return -1.0f;
	}

	// Intersection
	return minDistance;
}

Ray Raycaster::_calculateCursorRay(Ivec2 cursorPosition)
{
	Vec2 screenCoords = Tools::convertFromScreenCoords(cursorPosition);
	Vec2 ndcCoords = Math::convertToNDC(screenCoords);
	Vec4 clipCoords = Vec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	Vec4 viewCoords = _convertToViewSpace(clipCoords);
	Vec3 worldCoords = _convertToWorldSpace(viewCoords);

	return Ray(_renderBus.getCameraPosition(), Math::normalizeVector(worldCoords));
}

Vec4 Raycaster::_convertToViewSpace(Vec4 clipCoords)
{
	Matrix44 invertedProjection = Math::invertMatrix(_renderBus.getProjectionMatrix());
	Vec4 viewCoords = (invertedProjection * clipCoords);

	return Vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

Vec3 Raycaster::_convertToWorldSpace(Vec4 viewCoords)
{
	Matrix44 invertedView = Math::invertMatrix(_renderBus.getViewMatrix());
	Vec4 worldCoords = (invertedView * viewCoords);

	return Vec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

Vec3 Raycaster::getPointOnRay(Ray ray, float distance)
{
	return (ray.getPosition() + (ray.getDirection() * distance));
}

bool Raycaster::_isUnderTerrain(float distance)
{
	// Scale ray
	Vec3 scaledRay = getPointOnRay(_cursorRay, distance);

	// Retrieve height
	auto selectedTerrain = _terrainManager.getSelectedTerrain();
	float terrainHeight = _terrainManager.getPixelHeight(
		selectedTerrain->getID(),
		scaledRay.x + (selectedTerrain->getSize() / 2.0f), 
		scaledRay.z + (selectedTerrain->getSize() / 2.0f));

	// Return
	return (scaledRay.y < terrainHeight);
}

Vec3 Raycaster::_calculateTerrainPoint()
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
			distance -= (_terrainPointingPrecision / 2.0f);
			Vec3 endPoint = getPointOnRay(_cursorRay, distance);

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