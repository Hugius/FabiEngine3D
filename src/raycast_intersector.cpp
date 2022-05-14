#include "raycast_intersector.hpp"

using std::min;
using std::max;
using std::make_shared;

void RaycastIntersector::update()
{
	if(_isTerrainIntersectionEnabled && (_terrainManager->getSelectedTerrain() != nullptr))
	{
		_terrainId = _terrainManager->getSelectedTerrain()->getId();
		_pointOnTerrain = _calculatePointOnTerrain();
		_distanceToTerrain = _calculateDistanceToTerrain();
	}
	else
	{
		_terrainId = "";
		_pointOnTerrain = fvec3(-1.0f);
		_distanceToTerrain = -1.0f;
	}

	_closestAabbId = "";
	_aabbIntersections.clear();

	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		if(!_isAabbIntersectionEnabled || !aabb->isRaycastResponsive())
		{
			_aabbIntersections.insert({aabb->getId(), -1.0f});

			continue;
		}

		auto distanceToAabb = _calculateDistanceToAabb(aabb);

		if(_isTerrainIntersectionEnabled)
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

		_aabbIntersections.insert({aabb->getId(), distanceToAabb});

		if(distanceToAabb != -1.0f)
		{
			if(_closestAabbId.empty() || (distanceToAabb < _aabbIntersections.at(_closestAabbId)))
			{
				_closestAabbId = aabb->getId();
			}
		}
	}
}

void RaycastIntersector::inject(shared_ptr<RaycastCalculator> raycastCalculator)
{
	_raycastCalculator = raycastCalculator;
}

void RaycastIntersector::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void RaycastIntersector::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void RaycastIntersector::setTerrainIntersectionEnabled(bool value)
{
	_isTerrainIntersectionEnabled = value;
}

void RaycastIntersector::setTerrainIntersectionDistance(float distance)
{
	_terrainIntersectionDistance = distance;
}

void RaycastIntersector::setTerrainIntersectionPrecision(float precision)
{
	_terrainIntersectionPrecision = precision;
}

void RaycastIntersector::setAabbIntersectionEnabled(bool value)
{
	_isAabbIntersectionEnabled = value;
}

void RaycastIntersector::resetTerrainStatus(const string & terrainId)
{
	if(terrainId == _terrainId)
	{
		_terrainId = "";
	}
}

void RaycastIntersector::resetAabbStatus(const string & aabbId)
{
	if(aabbId == _closestAabbId)
	{
		_closestAabbId = "";
	}

	if(_aabbIntersections.find(aabbId) != _aabbIntersections.end())
	{
		_aabbIntersections.erase(aabbId);
	}
}

const string & RaycastIntersector::getTerrainId() const
{
	return _terrainId;
}

const string & RaycastIntersector::getClosestAabbId() const
{
	return _closestAabbId;
}

const bool RaycastIntersector::isTerrainIntersectionEnabled() const
{
	return _isTerrainIntersectionEnabled;
}

const bool RaycastIntersector::isAabbIntersectionEnabled() const
{
	return _isAabbIntersectionEnabled;
}

const float RaycastIntersector::getTerrainIntersectionDistance() const
{
	return _terrainIntersectionDistance;
}

const float RaycastIntersector::getTerrainIntersectionPrecision() const
{
	return _terrainIntersectionPrecision;
}

const float RaycastIntersector::getDistanceToTerrain() const
{
	return _distanceToTerrain;
}

const float RaycastIntersector::getDistanceToAabb(const string & aabbId) const
{
	return _aabbIntersections.at(aabbId);
}

const fvec3 & RaycastIntersector::getPointOnTerrain() const
{
	return _pointOnTerrain;
}

const float RaycastIntersector::_calculateRayBoxIntersectionDistance(const shared_ptr<Ray> ray, const shared_ptr<Box> box) const
{
	/*
		https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms

		Initial formula: point = (origin + distance) * direction
		Rearranged formula: distance = (point - origin) / direction
		Final formula: distance = (point - origin) * (1 / direction)
	*/

	if(ray->getDirection() == fvec3(0.0f))
	{
		return -1.0f;
	}

	const auto invertedRayDirection = (fvec3(1.0f) / ray->getDirection());
	const auto minX = (box->getPosition().x - box->getLeft());
	const auto maxX = (box->getPosition().x + box->getRight());
	const auto minY = (box->getPosition().y - box->getBottom());
	const auto maxY = (box->getPosition().y + box->getTop());
	const auto minZ = (box->getPosition().z - box->getBack());
	const auto maxZ = (box->getPosition().z + box->getFront());
	const auto minDistanceX = ((minX - ray->getPosition().x) * invertedRayDirection.x);
	const auto maxDistanceX = ((maxX - ray->getPosition().x) * invertedRayDirection.x);
	const auto minDistanceY = ((minY - ray->getPosition().y) * invertedRayDirection.y);
	const auto maxDistanceY = ((maxY - ray->getPosition().y) * invertedRayDirection.y);
	const auto minDistanceZ = ((minZ - ray->getPosition().z) * invertedRayDirection.z);
	const auto maxDistanceZ = ((maxZ - ray->getPosition().z) * invertedRayDirection.z);
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
	const auto selectedTerrain = _terrainManager->getSelectedTerrain();
	const auto terrainHeight = _terrainManager->getTerrainPixelHeight(selectedTerrain->getId(), pointOnRay.x + (selectedTerrain->getSize() * 0.5f), pointOnRay.z + (selectedTerrain->getSize() * 0.5f));

	return (pointOnRay.y < terrainHeight);
}

const fvec3 RaycastIntersector::_calculatePointOnTerrain() const
{
	float distance = 0.0f;

	while(distance < _terrainIntersectionDistance)
	{
		if(_isUnderTerrain(distance))
		{
			distance -= (_terrainIntersectionPrecision * 0.5f);

			const auto endPoint = _raycastCalculator->calculatePointOnRay(_raycastCalculator->getCursorRay(), distance);
			const auto selectedTerrain = _terrainManager->getSelectedTerrain();

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
			distance += _terrainIntersectionPrecision;
		}
	}

	return fvec3(-1.0f);
}

const float RaycastIntersector::_calculateDistanceToTerrain() const
{
	if(_pointOnTerrain == fvec3(-1.0f))
	{
		return -1.0f;
	}

	return Mathematics::calculateDistance(_raycastCalculator->getCursorRay()->getPosition(), _pointOnTerrain);
}

const float RaycastIntersector::_calculateDistanceToAabb(shared_ptr<Aabb> aabb) const
{
	if(aabb->isCentered())
	{
		const auto position = aabb->getBasePosition();
		const auto left = (aabb->getBaseSize().x * 0.5f);
		const auto right = (aabb->getBaseSize().x * 0.5f);
		const auto bottom = (aabb->getBaseSize().y * 0.5f);
		const auto top = (aabb->getBaseSize().y * 0.5f);
		const auto back = (aabb->getBaseSize().z * 0.5f);
		const auto front = (aabb->getBaseSize().z * 0.5f);
		const auto box = make_shared<Box>(position, left, right, bottom, top, back, front);

		return _calculateRayBoxIntersectionDistance(_raycastCalculator->getCursorRay(), box);
	}
	else
	{
		const auto position = aabb->getBasePosition();
		const auto left = (aabb->getBaseSize().x * 0.5f);
		const auto right = (aabb->getBaseSize().x * 0.5f);
		const auto bottom = 0.0f;
		const auto top = aabb->getBaseSize().y;
		const auto back = (aabb->getBaseSize().z * 0.5f);
		const auto front = (aabb->getBaseSize().z * 0.5f);
		const auto box = make_shared<Box>(position, left, right, bottom, top, back, front);

		return _calculateRayBoxIntersectionDistance(_raycastCalculator->getCursorRay(), box);
	}
}