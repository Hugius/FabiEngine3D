#include "raycast_intersector.hpp"

using std::make_shared;

void RaycastIntersector::calculateTerrainIntersection(float maxDistance, float precision)
{
	if(_terrainManager->getSelectedTerrain() == nullptr)
	{
		clearTerrainIntersection();
	}
	else
	{
		_pointOnTerrain = _getPointOnTerrain(maxDistance, precision);
		_distanceToTerrain = _getDistanceToTerrain();
	}
}

void RaycastIntersector::calculateAabbsIntersection()
{
	clearAabbsIntersection();

	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		if(!aabb->isRaycastResponsive())
		{
			_aabbIntersections.insert({aabb->getId(), -1.0f});

			continue;
		}

		auto distanceToAabb = _getDistanceToAabb(aabb);

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

void RaycastIntersector::clearTerrainIntersection()
{
	_pointOnTerrain = fvec3(-1.0f);
	_distanceToTerrain = -1.0f;
}

void RaycastIntersector::clearAabbsIntersection()
{
	_closestAabbId = "";

	_aabbIntersections.clear();
}

const vector<string> RaycastIntersector::getAabbIds() const
{
	vector<string> aabbIds = {};

	for(const auto & [aabbId, distance] : _aabbIntersections)
	{
		if(distance != -1.0f)
		{
			aabbIds.push_back(aabbId);
		}
	}

	return aabbIds;
}

RaycastIntersector::RaycastIntersector()
{
	clearTerrainIntersection();
	clearAabbsIntersection();
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

const string & RaycastIntersector::getClosestAabbId() const
{
	return _closestAabbId;
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

const float RaycastIntersector::_getDistanceBetweenRayAndBox(shared_ptr<Ray> ray, shared_ptr<Box> box) const
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

const bool RaycastIntersector::_isInsideTerrain(float distance) const
{
	const auto pointOnRay = RaycastCalculator::calculatePointOnRay(_raycastCalculator->getCursorRay(), distance);
	const auto selectedTerrain = _terrainManager->getSelectedTerrain();
	const auto terrainHeight = _terrainManager->getTerrainPixelHeight(selectedTerrain->getId(), pointOnRay.x + (selectedTerrain->getSize() * 0.5f), pointOnRay.z + (selectedTerrain->getSize() * 0.5f));

	return (pointOnRay.y < terrainHeight);
}

const fvec3 RaycastIntersector::_getPointOnTerrain(float maxDistance, float precision) const
{
	float distance = 0.0f;

	while(distance < maxDistance)
	{
		if(_isInsideTerrain(distance))
		{
			distance -= (precision * 0.5f);

			const auto endPoint = RaycastCalculator::calculatePointOnRay(_raycastCalculator->getCursorRay(), distance);
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
			distance += precision;
		}
	}

	return fvec3(-1.0f);
}

const float RaycastIntersector::_getDistanceToTerrain() const
{
	if(_pointOnTerrain == fvec3(-1.0f))
	{
		return -1.0f;
	}

	return Mathematics::calculateDistance(_raycastCalculator->getCursorRay()->getPosition(), _pointOnTerrain);
}

const float RaycastIntersector::_getDistanceToAabb(shared_ptr<Aabb> aabb) const
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

		return _getDistanceBetweenRayAndBox(_raycastCalculator->getCursorRay(), box);
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

		return _getDistanceBetweenRayAndBox(_raycastCalculator->getCursorRay(), box);
	}
}