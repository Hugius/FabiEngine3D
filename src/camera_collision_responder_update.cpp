#include "camera_collision_responder.hpp"

void CameraCollisionResponder::update()
{
	_isCameraUnderTerrain = false;

	if(_isCameraTerrainResponseEnabled)
	{
		if(_terrainManager->getSelectedEntity() != nullptr)
		{
			fvec3 cameraPosition = _camera->getPosition();
			const float terrainX = (cameraPosition.x + (_terrainManager->getSelectedEntity()->getSize() * 0.5f));
			const float terrainZ = (cameraPosition.z + (_terrainManager->getSelectedEntity()->getSize() * 0.5f));
			const float terrainY = (_terrainManager->getPixelHeight(_terrainManager->getSelectedEntity()->getId(), terrainX, terrainZ) + _cameraTerrainResponseHeight);

			if(cameraPosition.y < terrainY)
			{
				_isCameraUnderTerrain = true;

				_camera->move(fvec3(0.0f, fabsf(cameraPosition.y - terrainY) * _cameraTerrainResponseSpeed, 0.0f));

				cameraPosition.y = _camera->getPosition().y;

				if(cameraPosition.y > terrainY)
				{
					_camera->setPosition(fvec3(cameraPosition.x, terrainY, cameraPosition.z));
				}
			}
		}
	}

	if(_isCameraAabbResponseEnabledX || _isCameraAabbResponseEnabledY || _isCameraAabbResponseEnabledZ)
	{
		unsigned int xPriority = 0;
		unsigned int yPriority = 0;
		unsigned int zPriority = 0;

		for(const auto & [entityId, entity] : _aabbManager->getEntities())
		{
			entity->setCollided(false);
		}

		switch(_responseDirectionOrder)
		{
			case DirectionOrderType::XYZ:
			{
				xPriority = 3; yPriority = 2; zPriority = 1;
				xPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				break;
			}
			case DirectionOrderType::XZY:
			{
				xPriority = 3; zPriority = 2; yPriority = 1;
				xPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				break;
			}
			case DirectionOrderType::YXZ:
			{
				yPriority = 3; xPriority = 1; zPriority = 2;
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				xPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				break;
			}
			case DirectionOrderType::YZX:
			{
				yPriority = 3; zPriority = 2; xPriority = 1;
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				break;
			}
			case DirectionOrderType::ZXY:
			{
				zPriority = 3; xPriority = 2; yPriority = 1;
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				xPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				break;
			}
			case DirectionOrderType::ZYX:
			{
				zPriority = 3; yPriority = 2; xPriority = 1;
				zPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Z));
				yPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::Y));
				xPriority *= static_cast<unsigned int>(_handleCollision(DirectionType::X));
				break;
			}
		}

		if((xPriority > yPriority) && (xPriority > zPriority) && (yPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrderType::XYZ;
		}
		if((xPriority > yPriority) && (xPriority > zPriority) && (zPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrderType::XZY;
		}
		if((yPriority > xPriority) && (yPriority > zPriority) && (xPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrderType::YXZ;
		}
		if((yPriority > xPriority) && (yPriority > zPriority) && (zPriority >= xPriority))
		{
			_responseDirectionOrder = DirectionOrderType::YZX;
		}
		if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrderType::ZYX;
		}
		if((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrderType::ZXY;
		}

		_lastCameraPosition = _camera->getPosition();
	}
}