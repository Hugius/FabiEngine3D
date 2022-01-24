#include "camera_collision_handler.hpp"

void CameraCollisionHandler::update()
{
	_isCameraUnderTerrain = false;
	if(_isCameraTerrainResponseEnabled)
	{
		if(_terrainManager->getSelectedEntity() != nullptr)
		{
			fvec3 cameraPosition = _camera->getPosition();
			const float terrainX = (cameraPosition.x + (_terrainManager->getSelectedEntity()->getSize() / 2.0f));
			const float terrainZ = (cameraPosition.z + (_terrainManager->getSelectedEntity()->getSize() / 2.0f));
			const float terrainY = (_terrainManager->getPixelHeight(_terrainManager->getSelectedEntity()->getId(), terrainX, terrainZ) + _cameraTerrainHeight);

			if(cameraPosition.y < terrainY)
			{
				_isCameraUnderTerrain = true;

				_camera->move(fvec3(0.0f, fabsf(cameraPosition.y - terrainY) * _cameraTerrainSpeed, 0.0f));
				cameraPosition.y = _camera->getPosition().y;

				if(cameraPosition.y > terrainY)
				{
					_camera->setPosition(fvec3(cameraPosition.x, terrainY, cameraPosition.z));
				}
			}
		}
	}

	if(_isCameraAabbResponseEnabled)
	{
		unsigned int xPriority = 0;
		unsigned int yPriority = 0;
		unsigned int zPriority = 0;

		for(const auto& [key, aabb] : _aabbManager->getEntities())
		{
			aabb->setCollided(false);
		}

		switch(_responseDirectionOrder)
		{
			case DirectionOrder::XYZ:
			{
				xPriority = 3; yPriority = 2; zPriority = 1;
				xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				break;
			}
			case DirectionOrder::XZY:
			{
				xPriority = 3; zPriority = 2; yPriority = 1;
				xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				break;
			}
			case DirectionOrder::YXZ:
			{
				yPriority = 3; xPriority = 1; zPriority = 2;
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				break;
			}
			case DirectionOrder::YZX:
			{
				yPriority = 3; zPriority = 2; xPriority = 1;
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				break;
			}
			case DirectionOrder::ZXY:
			{
				zPriority = 3; xPriority = 2; yPriority = 1;
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				break;
			}
			case DirectionOrder::ZYX:
			{
				zPriority = 3; yPriority = 2; xPriority = 1;
				zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z));
				yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y));
				xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X));
				break;
			}
		}

		if((xPriority > yPriority) && (xPriority > zPriority) && (yPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrder::XYZ;
		}
		if((xPriority > yPriority) && (xPriority > zPriority) && (zPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::XZY;
		}
		if((yPriority > xPriority) && (yPriority > zPriority) && (xPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrder::YXZ;
		}
		if((yPriority > xPriority) && (yPriority > zPriority) && (zPriority >= xPriority))
		{
			_responseDirectionOrder = DirectionOrder::YZX;
		}
		if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::ZYX;
		}
		if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::ZXY;
		}

		_lastCameraPosition = _camera->getPosition();
	}
}