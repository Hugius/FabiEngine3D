#include "ray_caster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::min;
using std::max;

RayCaster::RayCaster(RenderBus& renderBus, TerrainEntityManager& terrainManager)
	:
	_renderBus(renderBus),
	_terrainManager(terrainManager)
{

}

void RayCaster::update(Ivec2 cursorPosition)
{
	// Update raycasting
	_cursorRay = _getCursorRay(cursorPosition);

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

bool RayCaster::isTerrainPointingEnabled()
{
	return _isTerrainPointingEnabled;
}

float RayCaster::getTerrainPointingDistance()
{
	return _terrainPointingDistance;
}

float RayCaster::getTerrainPointingPrecision()
{
	return _terrainPointingPrecision;
}

// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
float RayCaster::checkCursorInBox(Vec3 leftBottomCoordinate, Vec3 rightTopCoordinate, Vec3 cameraPosition)
{
	// Ray direction
	Vec3 rayDirection;
	rayDirection.x = (1.0f / _cursorRay.x);
	rayDirection.y = (1.0f / _cursorRay.y);
	rayDirection.z = (1.0f / _cursorRay.z);

	// Calculates distances between camera & collision
	float distance1 = ((leftBottomCoordinate.x - cameraPosition.x) * rayDirection.x);
	float distance2 = ((rightTopCoordinate.x - cameraPosition.x) * rayDirection.x);
	float distance3 = ((leftBottomCoordinate.y - cameraPosition.y) * rayDirection.y);
	float distance4 = ((rightTopCoordinate.y - cameraPosition.y) * rayDirection.y);
	float distance5 = ((leftBottomCoordinate.z - cameraPosition.z) * rayDirection.z);
	float distance6 = ((rightTopCoordinate.z - cameraPosition.z) * rayDirection.z);
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
	else
	{
		// Intersection
		return minDistance;
	}
}

Vec3 RayCaster::_getCursorRay(Ivec2 cursorPosition)
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
	Matrix44 invertedProjection = Math::invertMatrix(_renderBus.getProjectionMatrix());
	Vec4 viewCoords = (invertedProjection * value);

	return Vec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

Vec3 RayCaster::_convertToWorldSpace(Vec4 value)
{
	Matrix44 invertedView = Math::invertMatrix(_renderBus.getViewMatrix());
	Vec4 worldCoords = (invertedView * value);
	worldCoords = Math::normalizeVector(worldCoords);

	return Vec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

Vec3 RayCaster::_getPointOnRay(float distance)
{
	Vec3 cameraPosition = _renderBus.getCameraPosition();
	Vec3 scaledRay = (_cursorRay * distance);

	return (cameraPosition + scaledRay);
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
	return _cursorRay;
}

Vec3 RayCaster::getTerrainPoint()
{
	return _terrainPoint;
}