#include "raycaster.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "mathematics.hpp"

#include <algorithm>

using std::min;
using std::max;

void Raycaster::update(const ivec2& cursorPosition)
{
	_cursorRay = _calculateCursorRay(cursorPosition);

	if(_isTerrainPointingEnabled)
	{
		if(_terrainManager->getSelectedEntity() != nullptr)
		{
			_terrainPoint = _calculateTerrainPoint();
		}
		else
		{
			_terrainPoint = fvec3(-1.0f);
		}
	}
	else
	{
		_terrainPoint = fvec3(-1.0f);
	}
}

void Raycaster::inject(shared_ptr<RenderBus> renderBus)
{
	_renderBus = renderBus;
}

void Raycaster::inject(shared_ptr<TerrainEntityManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void Raycaster::setTerrainPointingEnabled(bool value)
{
	_isTerrainPointingEnabled = value;
}

void Raycaster::setTerrainPointingDistance(float distance)
{
	_terrainPointingDistance = distance;
}

void Raycaster::setTerrainPointingPrecision(float precision)
{
	_terrainPointingPrecision = precision;
}

const bool Raycaster::isTerrainPointingEnabled() const
{
	return _isTerrainPointingEnabled;
}

const float Raycaster::getTerrainPointingDistance() const
{
	return _terrainPointingDistance;
}

const float Raycaster::getTerrainPointingPrecision() const
{
	return _terrainPointingPrecision;
}

const Ray& Raycaster::getCursorRay() const
{
	return _cursorRay;
}

const fvec3& Raycaster::getTerrainPoint() const
{
	return _terrainPoint;
}

/* https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms */
const float Raycaster::calculateRayBoxIntersectionDistance(const Ray& ray, const Box& box) const
{
	/*
		Initial formula: point = (origin + distance) * direction
		Rearranged formula: distance = (point - origin) / direction
		Final formula: distance = (point - origin) * (1 / direction)
	*/

	if(ray.getDirection() == fvec3(0.0f))
	{
		return -1.0f;
	}

	const fvec3 inverseRayDirection = (fvec3(1.0f) / ray.getDirection());

	float minX = (box.getPosition().x - box.getLeft());
	float maxX = (box.getPosition().x + box.getRight());
	float minY = (box.getPosition().y - box.getBottom());
	float maxY = (box.getPosition().y + box.getTop());
	float minZ = (box.getPosition().z - box.getBack());
	float maxZ = (box.getPosition().z + box.getFront());

	float minDistanceX = ((minX - ray.getPosition().x) * inverseRayDirection.x);
	float maxDistanceX = ((maxX - ray.getPosition().x) * inverseRayDirection.x);
	float minDistanceY = ((minY - ray.getPosition().y) * inverseRayDirection.y);
	float maxDistanceY = ((maxY - ray.getPosition().y) * inverseRayDirection.y);
	float minDistanceZ = ((minZ - ray.getPosition().z) * inverseRayDirection.z);
	float maxDistanceZ = ((maxZ - ray.getPosition().z) * inverseRayDirection.z);

	float minIntersectionDistance = max(max(min(minDistanceX, maxDistanceX), min(minDistanceY, maxDistanceY)), min(minDistanceZ, maxDistanceZ));
	float maxIntersectionDistance = min(min(max(minDistanceX, maxDistanceX), max(minDistanceY, maxDistanceY)), max(minDistanceZ, maxDistanceZ));

	if(maxIntersectionDistance < 0.0f)
	{
		return -1.0f;
	}

	if(minIntersectionDistance > maxIntersectionDistance)
	{
		return -1.0f;
	}

	return minIntersectionDistance;
}

const Ray Raycaster::_calculateCursorRay(const ivec2& cursorPosition) const
{
	fvec2 screenCoords = Tools::convertFromScreenCoords(cursorPosition);
	fvec2 ndcCoords = Math::convertToNdc(screenCoords);
	fvec4 clipCoords = fvec4(ndcCoords.x, ndcCoords.y, -1.0f, 1.0f);
	fvec4 viewCoords = _convertToViewSpace(clipCoords);
	fvec3 worldCoords = _convertToWorldSpace(viewCoords);

	return Ray(_renderBus->getCameraPosition(), Math::normalize(worldCoords));
}

const fvec4 Raycaster::_convertToViewSpace(const fvec4& clipCoords) const
{
	auto invertedProjection = Math::invertMatrix(_renderBus->getProjectionMatrix());
	auto viewCoords = (invertedProjection * clipCoords);

	return fvec4(viewCoords.x, viewCoords.y, -1.0f, 0.0f);
}

const fvec3 Raycaster::_convertToWorldSpace(const fvec4& viewCoords) const
{
	auto invertedView = Math::invertMatrix(_renderBus->getViewMatrix());
	auto worldCoords = (invertedView * viewCoords);

	return fvec3(worldCoords.x, worldCoords.y, worldCoords.z);
}

const fvec3 Raycaster::calculatePointOnRay(const Ray& ray, float distance) const
{
	return (ray.getPosition() + (ray.getDirection() * distance));
}

const bool Raycaster::_isUnderTerrain(float distance) const
{
	auto scaledRay = calculatePointOnRay(_cursorRay, distance);

	auto selectedTerrain = _terrainManager->getSelectedEntity();
	float terrainHeight = _terrainManager->getPixelHeight(selectedTerrain->getId(), scaledRay.x + (selectedTerrain->getSize() / 2.0f), scaledRay.z + (selectedTerrain->getSize() / 2.0f));

	return (scaledRay.y < terrainHeight);
}

const fvec3 Raycaster::_calculateTerrainPoint() const
{
	float distance = 0.0f;

	while(distance < _terrainPointingDistance)
	{
		if(_isUnderTerrain(distance))
		{
			distance -= (_terrainPointingPrecision / 2.0f);

			fvec3 endPoint = calculatePointOnRay(_cursorRay, distance);

			auto selectedTerrain = _terrainManager->getSelectedEntity();

			if(_terrainManager->isInside(selectedTerrain->getId(), (endPoint.x + (selectedTerrain->getSize() / 2.0f)), (endPoint.z + (selectedTerrain->getSize() / 2.0f))))
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

	return fvec3(-1.0f);
}