#include "raycast_intersector.hpp"

using std::min;
using std::max;
using std::make_pair;

void RaycastIntersector::update()
{
	if(_isTerrainPointingEnabled && (_terrainManager->getSelectedEntity() != nullptr))
	{
		_terrainPoint = _calculateTerrainPoint();
		_distanceToTerrain = _calculateDistanceToTerrain();
	}
	else
	{
		_terrainPoint = fvec3(0.0f);
		_distanceToTerrain = -1.0f;
	}

	_closestAabbId = "";
	_aabbIntersections.clear();

	for(const auto& [key, entity] : _aabbManager->getEntities())
	{
		if(!entity->isRaycastResponsive())
		{
			_aabbIntersections.insert(make_pair(entity->getId(), -1.0f));
			continue;
		}

		float distanceToAabb = _calculateDistanceToAabb(entity);

		if(_isTerrainPointingEnabled)
		{
			if(_distanceToTerrain != -1.0f)
			{
				if(distanceToAabb != -1.0f)
				{
					if(_distanceToTerrain < distanceToAabb)
					{
						distanceToAabb = -1.0f;
					}
				}
			}
		}

		_aabbIntersections.insert(make_pair(entity->getId(), distanceToAabb));

		if(distanceToAabb != -1.0f)
		{
			if(_closestAabbId.empty() || (distanceToAabb < _aabbIntersections.at(_closestAabbId)))
			{
				_closestAabbId = entity->getId();
			}
		}
	}
}

void RaycastIntersector::inject(shared_ptr<RaycastCalculator> raycastCalculator)
{
	_raycastCalculator = raycastCalculator;
}

void RaycastIntersector::inject(shared_ptr<TerrainEntityManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void RaycastIntersector::inject(shared_ptr<AabbEntityManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void RaycastIntersector::setTerrainPointingEnabled(bool value)
{
	_isTerrainPointingEnabled = value;
}

void RaycastIntersector::setTerrainPointingDistance(float distance)
{
	_terrainPointingDistance = distance;
}

void RaycastIntersector::setTerrainPointingPrecision(float precision)
{
	_terrainPointingPrecision = precision;
}

const string& RaycastIntersector::getClosestAabbId() const
{
	return _closestAabbId;
}

const bool RaycastIntersector::isTerrainPointingEnabled() const
{
	return _isTerrainPointingEnabled;
}

const float RaycastIntersector::getTerrainPointingDistance() const
{
	return _terrainPointingDistance;
}

const float RaycastIntersector::getTerrainPointingPrecision() const
{
	return _terrainPointingPrecision;
}

const float RaycastIntersector::getDistanceToTerrain() const
{
	return _distanceToTerrain;
}

const float RaycastIntersector::getDistanceToAabb(const string& id) const
{
	return _aabbIntersections.at(id);
}

const fvec3& RaycastIntersector::getTerrainPoint() const
{
	return _terrainPoint;
}

/* https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms */
const float RaycastIntersector::_calculateRayBoxIntersectionDistance(const shared_ptr<Ray> ray, const shared_ptr<Box> box) const
{
	/*
		Initial formula: point = (origin + distance) * direction
		Rearranged formula: distance = (point - origin) / direction
		Final formula: distance = (point - origin) * (1 / direction)
	*/

	if(ray->getDirection() == fvec3(0.0f))
	{
		return -1.0f;
	}

	const auto inverseRayDirection = (fvec3(1.0f) / ray->getDirection());

	const auto minX = (box->getPosition().x - box->getLeft());
	const auto maxX = (box->getPosition().x + box->getRight());
	const auto minY = (box->getPosition().y - box->getBottom());
	const auto maxY = (box->getPosition().y + box->getTop());
	const auto minZ = (box->getPosition().z - box->getBack());
	const auto maxZ = (box->getPosition().z + box->getFront());

	const auto minDistanceX = ((minX - ray->getPosition().x) * inverseRayDirection.x);
	const auto maxDistanceX = ((maxX - ray->getPosition().x) * inverseRayDirection.x);
	const auto minDistanceY = ((minY - ray->getPosition().y) * inverseRayDirection.y);
	const auto maxDistanceY = ((maxY - ray->getPosition().y) * inverseRayDirection.y);
	const auto minDistanceZ = ((minZ - ray->getPosition().z) * inverseRayDirection.z);
	const auto maxDistanceZ = ((maxZ - ray->getPosition().z) * inverseRayDirection.z);

	const auto minIntersectionDistance = max(max(min(minDistanceX, maxDistanceX), min(minDistanceY, maxDistanceY)), min(minDistanceZ, maxDistanceZ));
	const auto maxIntersectionDistance = min(min(max(minDistanceX, maxDistanceX), max(minDistanceY, maxDistanceY)), max(minDistanceZ, maxDistanceZ));

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

const bool RaycastIntersector::_isUnderTerrain(float distance) const
{
	const auto pointOnRay = _raycastCalculator->calculatePointOnRay(_raycastCalculator->getCursorRay(), distance);
	const auto selectedTerrain = _terrainManager->getSelectedEntity();
	const auto terrainHeight = _terrainManager->getPixelHeight(selectedTerrain->getId(), pointOnRay.x + (selectedTerrain->getSize() * 0.5f), pointOnRay.z + (selectedTerrain->getSize() * 0.5f));

	return (pointOnRay.y < terrainHeight);
}

const fvec3 RaycastIntersector::_calculateTerrainPoint() const
{
	float distance = 0.0f;

	while(distance < _terrainPointingDistance)
	{
		if(_isUnderTerrain(distance))
		{
			distance -= (_terrainPointingPrecision * 0.5f);

			fvec3 endPoint = _raycastCalculator->calculatePointOnRay(_raycastCalculator->getCursorRay(), distance);

			auto selectedTerrain = _terrainManager->getSelectedEntity();

			if(_terrainManager->isInside(selectedTerrain->getId(), (endPoint.x + (selectedTerrain->getSize() * 0.5f)), (endPoint.z + (selectedTerrain->getSize() * 0.5f))))
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

const float RaycastIntersector::_calculateDistanceToTerrain() const
{
	return Math::calculateDistance(_raycastCalculator->getCursorRay()->getPosition(), _terrainPoint);
}

const float RaycastIntersector::_calculateDistanceToAabb(shared_ptr<AabbEntity> entity) const
{
	if(entity->isCentered())
	{
		const auto position = entity->getPosition();
		const auto left = (entity->getSize().x * 0.5f);
		const auto right = (entity->getSize().x * 0.5f);
		const auto bottom = (entity->getSize().y * 0.5f);
		const auto top = (entity->getSize().y * 0.5f);
		const auto back = (entity->getSize().z * 0.5f);
		const auto front = (entity->getSize().z * 0.5f);
		const auto box = make_shared<Box>(position, left, right, bottom, top, back, front);

		return _calculateRayBoxIntersectionDistance(_raycastCalculator->getCursorRay(), box);
	}
	else
	{
		const auto position = entity->getPosition();
		const auto left = (entity->getSize().x * 0.5f);
		const auto right = (entity->getSize().x * 0.5f);
		const auto bottom = 0.0f;
		const auto top = entity->getSize().y;
		const auto back = (entity->getSize().z * 0.5f);
		const auto front = (entity->getSize().z * 0.5f);
		const auto box = make_shared<Box>(position, left, right, bottom, top, back, front);

		return _calculateRayBoxIntersectionDistance(_raycastCalculator->getCursorRay(), box);
	}
}