#include "camera_collision_handler.hpp"

void CameraCollisionHandler::calculateTerrainCollision(bool mustRespondY)
{
	if(_terrainManager->getSelectedTerrain() == nullptr)
	{
		_terrainId = "";
		_isCameraUnderTerrain = false;
	}
	else
	{
		_terrainId = _terrainManager->getSelectedTerrain()->getId();
		_isCameraUnderTerrain = false;

		auto cameraPosition = _camera->getPosition();

		const auto terrainX = (cameraPosition.x + (_terrainManager->getSelectedTerrain()->getSize() * 0.5f));
		const auto terrainZ = (cameraPosition.z + (_terrainManager->getSelectedTerrain()->getSize() * 0.5f));
		const auto terrainY = (_terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), terrainX, terrainZ) + _cameraTerrainResponseHeight);

		if(cameraPosition.y < terrainY)
		{
			_isCameraUnderTerrain = true;

			if(mustRespondY)
			{
				_camera->move(fvec3(0.0f, fabsf(cameraPosition.y - terrainY) * _cameraTerrainResponseSpeed, 0.0f));

				cameraPosition.y = _camera->getPosition().y;

				if(cameraPosition.y > terrainY)
				{
					_camera->setPosition(fvec3(cameraPosition.x, terrainY, cameraPosition.z));
				}
			}
		}
	}
}

void CameraCollisionHandler::calculateAabbCollision(bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	_aabbCollisions.clear();

	int xPriority = 0;
	int yPriority = 0;
	int zPriority = 0;

	switch(_responseDirectionOrder)
	{
		case DirectionOrderType::XYZ:
		{
			xPriority = 3; yPriority = 2; zPriority = 1;

			xPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::XZY:
		{
			xPriority = 3; zPriority = 2; yPriority = 1;

			xPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::YXZ:
		{
			yPriority = 3; xPriority = 1; zPriority = 2;

			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::YZX:
		{
			yPriority = 3; zPriority = 2; xPriority = 1;
			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::ZXY:
		{
			zPriority = 3; xPriority = 2; yPriority = 1;

			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
		case DirectionOrderType::ZYX:
		{
			zPriority = 3; yPriority = 2; xPriority = 1;

			zPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Z, mustRespondX, mustRespondY, mustRespondZ));
			yPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::Y, mustRespondX, mustRespondY, mustRespondZ));
			xPriority *= static_cast<int>(_calculateAabbCollision(DirectionType::X, mustRespondX, mustRespondY, mustRespondZ));

			break;
		}
	}

	if((xPriority > yPriority) && (xPriority > zPriority) && (yPriority >= zPriority))
	{
		_responseDirectionOrder = DirectionOrderType::XYZ;
	}
	else if((xPriority > yPriority) && (xPriority > zPriority) && (zPriority >= yPriority))
	{
		_responseDirectionOrder = DirectionOrderType::XZY;
	}
	else if((yPriority > xPriority) && (yPriority > zPriority) && (xPriority >= zPriority))
	{
		_responseDirectionOrder = DirectionOrderType::YXZ;
	}
	else if((yPriority > xPriority) && (yPriority > zPriority) && (zPriority >= xPriority))
	{
		_responseDirectionOrder = DirectionOrderType::YZX;
	}
	else if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
	{
		_responseDirectionOrder = DirectionOrderType::ZYX;
	}
	else if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
	{
		_responseDirectionOrder = DirectionOrderType::ZXY;
	}

	_lastCameraPosition = _camera->getPosition();
}

const bool CameraCollisionHandler::_calculateAabbCollision(DirectionType direction, bool mustRespondX, bool mustRespondY, bool mustRespondZ)
{
	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		if(!aabb->isRaycastResponsive())
		{
			_aabbCollisions.insert({aabb->getId(), {false, DirectionType::X}});

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
					_aabbCollisions.insert({aabb->getId(), {true, DirectionType::X}});

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
					_aabbCollisions.insert({aabb->getId(), {true, DirectionType::Y}});

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
					_aabbCollisions.insert({aabb->getId(), {true, DirectionType::Z}});

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