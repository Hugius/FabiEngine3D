#include "camera_collision_handler.hpp"

void CameraCollisionHandler::calculateCollisionWithTerrain(bool mustRespondY, float responseSpeed)
{
	if(_terrainManager->getSelectedTerrain() == nullptr)
	{
		_isCameraUnderTerrain = false;
	}
	else
	{
		_isCameraUnderTerrain = _calculateCollisionWithTerrain(mustRespondY, responseSpeed);
	}
}

void CameraCollisionHandler::calculateCollisionWithAabbs(bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	_aabbCollisions.clear();

	int xPriority = 0;
	int yPriority = 0;
	int zPriority = 0;

	switch(_aabbResponseDirectionOrder)
	{
		case DirectionOrderType::XYZ:
		{
			xPriority = 3; yPriority = 2; zPriority = 1;

			xPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::XZY:
		{
			xPriority = 3; zPriority = 2; yPriority = 1;

			xPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::YXZ:
		{
			yPriority = 3; xPriority = 1; zPriority = 2;

			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::YZX:
		{
			yPriority = 3; zPriority = 2; xPriority = 1;
			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::ZXY:
		{
			zPriority = 3; xPriority = 2; yPriority = 1;

			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::ZYX:
		{
			zPriority = 3; yPriority = 2; xPriority = 1;

			zPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateCollisionWithAabbs(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
	}

	if((xPriority > yPriority) && (xPriority > zPriority) && (yPriority >= zPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::XYZ;
	}
	else if((xPriority > yPriority) && (xPriority > zPriority) && (zPriority >= yPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::XZY;
	}
	else if((yPriority > xPriority) && (yPriority > zPriority) && (xPriority >= zPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::YXZ;
	}
	else if((yPriority > xPriority) && (yPriority > zPriority) && (zPriority >= xPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::YZX;
	}
	else if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::ZYX;
	}
	else if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
	{
		_aabbResponseDirectionOrder = DirectionOrderType::ZXY;
	}

	_lastCameraPosition = _camera->getPosition();
}

const bool CameraCollisionHandler::_calculateCollisionWithTerrain(bool mustRespondY, float responseSpeed) const
{
	auto cameraPosition = _camera->getPosition();

	const auto terrainX = ((_terrainManager->getSelectedTerrain()->getSize() * 0.5f) + cameraPosition.x);
	const auto terrainZ = ((_terrainManager->getSelectedTerrain()->getSize() * 0.5f) + cameraPosition.z);
	const auto leftTerrainY = _terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), (terrainX - _cameraBox->getLeft()), terrainZ);
	const auto rightTerrainY = _terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), (terrainX + _cameraBox->getRight()), terrainZ);
	const auto backTerrainY = _terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), terrainX, (terrainZ - _cameraBox->getBack()));
	const auto frontTerrainY = _terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), terrainX, (terrainZ + _cameraBox->getFront()));
	const auto terrainY = (max(max(max(leftTerrainY, rightTerrainY), backTerrainY), frontTerrainY) + _cameraBox->getBottom());

	if(cameraPosition.y < terrainY)
	{
		if(mustRespondY)
		{
			_camera->move(fvec3(0.0f, (fabsf(cameraPosition.y - terrainY) * responseSpeed), 0.0f));

			cameraPosition.y = _camera->getPosition().y;

			if(cameraPosition.y > terrainY)
			{
				_camera->setPosition(fvec3(cameraPosition.x, terrainY, cameraPosition.z));
			}
		}

		return true;
	}

	return false;
}

const bool CameraCollisionHandler::_calculateCollisionWithAabbs(DirectionType direction, bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		if(!aabb->isRaycastResponsive())
		{
			continue;
		}

		switch(direction)
		{
			case DirectionType::X:
			{
				const auto middle = _camera->getPosition();
				const auto middleChange = (middle - _lastCameraPosition);
				const auto hasCollided = _isInsideAabbX(aabb, middle, middleChange, _cameraBox);

				if(hasCollided)
				{
					_aabbCollisions.push_back({aabb->getId(), DirectionType::X});

					if(mustRespondX)
					{
						_camera->setPosition(fvec3(_lastCameraPosition.x, middle.y, middle.z));

						return true;
					}
				}

				break;
			}
			case DirectionType::Y:
			{
				const auto middle = _camera->getPosition();
				const auto middleChange = (middle - _lastCameraPosition);
				const auto hasCollided = _isInsideAabbY(aabb, middle, middleChange, _cameraBox);

				if(hasCollided)
				{
					_aabbCollisions.push_back({aabb->getId(), DirectionType::Y});

					if(mustRespondY)
					{
						if(!_isCameraUnderTerrain)
						{
							_camera->setPosition(fvec3(middle.x, _lastCameraPosition.y, middle.z));

							return true;
						}
					}
				}

				break;
			}
			case DirectionType::Z:
			{
				const auto middle = _camera->getPosition();
				const auto middleChange = (middle - _lastCameraPosition);
				const auto hasCollided = _isInsideAabbZ(aabb, middle, middleChange, _cameraBox);

				if(hasCollided)
				{
					_aabbCollisions.push_back({aabb->getId(), DirectionType::Z});

					if(mustRespondZ)
					{
						_camera->setPosition(fvec3(middle.x, middle.y, _lastCameraPosition.z));

						return true;
					}
				}

				break;
			}
		}
	}

	return false;
}