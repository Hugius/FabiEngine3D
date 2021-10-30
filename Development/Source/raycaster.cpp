#include "raycaster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

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
	if(_isTerrainPointingEnabled)
	{
		if(_terrainManager.getSelectedTerrain() != nullptr)
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
float Raycaster::calculateRayBoxIntersectionDistance(Ray ray, Box box)
{
	/*
		Original formula: point = (origin + distance) * direction
		Rearranged formula: distance = (point - origin) / direction
		Final formula: distance = (point - origin) * (1 / direction)
	*/

	// Check if ray is invalid
	if(ray.getDirection() == Vec3(0.0f))
	{
		return -1.0f;
	}

	// Small performance optimization
	const Vec3 inverseRayDirection = (Vec3(1.0f) / ray.getDirection());

	// Calculate box points
	float minX = (box.getPosition().x - box.getLeft());
	float maxX = (box.getPosition().x + box.getRight());
	float minY = (box.getPosition().y - box.getBottom());
	float maxY = (box.getPosition().y + box.getTop());
	float minZ = (box.getPosition().z - box.getBack());
	float maxZ = (box.getPosition().z + box.getFront());

	// Calculates distances
	float minDistanceX = ((minX - ray.getPosition().x) * inverseRayDirection.x);
	float maxDistanceX = ((maxX - ray.getPosition().x) * inverseRayDirection.x);
	float minDistanceY = ((minY - ray.getPosition().y) * inverseRayDirection.y);
	float maxDistanceY = ((maxY - ray.getPosition().y) * inverseRayDirection.y);
	float minDistanceZ = ((minZ - ray.getPosition().z) * inverseRayDirection.z);
	float maxDistanceZ = ((maxZ - ray.getPosition().z) * inverseRayDirection.z);

	// Calculate intersections
	float minIntersectionDistance = max(max(min(minDistanceX, maxDistanceX), min(minDistanceY, maxDistanceY)), min(minDistanceZ, maxDistanceZ));
	float maxIntersectionDistance = min(min(max(minDistanceX, maxDistanceX), max(minDistanceY, maxDistanceY)), max(minDistanceZ, maxDistanceZ));

	// AABB is behind camera
	if(maxIntersectionDistance < 0.0f)
	{
		return -1.0f;
	}

	// No intersection
	if(minIntersectionDistance > maxIntersectionDistance)
	{
		return -1.0f;
	}

	// Intersection
	return minIntersectionDistance;
}

Ray Raycaster::_calculateCursorRay(Ivec2 cursorPosition)
{
	Vec2 screenCoords = Tools::convertFromScreenCoords(cursorPosition);
	Vec2 ndcCoords = Math::convertToNDC(screenCoords);
	Vec4 clipCoords = Vec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	Vec4 viewCoords = _convertToViewSpace(clipCoords);
	Vec3 worldCoords = _convertToWorldSpace(viewCoords);

	return Ray(_renderBus.getCameraPosition(), Math::normalize(worldCoords));
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
	while(distance < _terrainPointingDistance)
	{
		// Intersected with terrain
		if(_isUnderTerrain(distance))
		{
			// Calculate point on terrain
			distance -= (_terrainPointingPrecision / 2.0f);
			Vec3 endPoint = getPointOnRay(_cursorRay, distance);

			// Check if selected point is inside the terrain size
			auto selectedTerrain = _terrainManager.getSelectedTerrain();
			if(_terrainManager.isInside(
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