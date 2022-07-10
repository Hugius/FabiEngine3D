#include "camera_collision_handler.hpp"

void CameraCollisionHandler::update()
{
	_isCameraUnderTerrain = false;

	if(_isCameraTerrainResponseEnabled)
	{
		_handleTerrainCollision();
	}

	if(_isCameraAabbResponseEnabledX || _isCameraAabbResponseEnabledY || _isCameraAabbResponseEnabledZ)
	{
		int xPriority = 0;
		int yPriority = 0;
		int zPriority = 0;

		for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
		{
			aabb->setCollided(false);
		}

		switch(_responseDirectionOrder)
		{
			case DirectionOrderType::XYZ:
			{
				xPriority = 3; yPriority = 2; zPriority = 1;

				xPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));
				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));
				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));

				break;
			}
			case DirectionOrderType::XZY:
			{
				xPriority = 3; zPriority = 2; yPriority = 1;

				xPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));
				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));
				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));

				break;
			}
			case DirectionOrderType::YXZ:
			{
				yPriority = 3; xPriority = 1; zPriority = 2;

				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));
				xPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));
				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));

				break;
			}
			case DirectionOrderType::YZX:
			{
				yPriority = 3; zPriority = 2; xPriority = 1;
				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));
				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));
				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));

				break;
			}
			case DirectionOrderType::ZXY:
			{
				zPriority = 3; xPriority = 2; yPriority = 1;

				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));
				xPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));
				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));

				break;
			}
			case DirectionOrderType::ZYX:
			{
				zPriority = 3; yPriority = 2; xPriority = 1;

				zPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Z));
				yPriority *= static_cast<int>(_handleAabbCollision(DirectionType::Y));
				xPriority *= static_cast<int>(_handleAabbCollision(DirectionType::X));

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
}