#include "camera_collision_handler.hpp"

void CameraCollisionHandler::update(const unordered_map<string, shared_ptr<AabbEntity>>& aabbs,
	TerrainEntityManager& terrainManager, Camera& camera)
{
	_isCameraUnderTerrain = false;
	if (_isCameraTerrainResponseEnabled)
	{
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			fvec3 cameraPosition = camera.getPosition();
			const float terrainX = (cameraPosition.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f));
			const float terrainZ = (cameraPosition.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f));
			const float terrainY = (terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraTerrainHeight);

			if (cameraPosition.y < terrainY)
			{
				_isCameraUnderTerrain = true;

				camera.move(fvec3(0.0f, fabsf(cameraPosition.y - terrainY) * _cameraTerrainSpeed, 0.0f));
				cameraPosition.y = camera.getPosition().y;

				if (cameraPosition.y > terrainY)
				{
					camera.setPosition(fvec3(cameraPosition.x, terrainY, cameraPosition.z));
				}
			}
		}
	}

	if (_isCameraAabbResponseEnabled)
	{
		unsigned int xPriority = 0;
		unsigned int yPriority = 0;
		unsigned int zPriority = 0;

		for (const auto& [key, aabb] : aabbs)
		{
			aabb->setCollided(false);
		}

		switch (_responseDirectionOrder)
		{
		case DirectionOrder::XYZ:
		{
			xPriority = 3; yPriority = 2; zPriority = 1;
			xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			break;
		}
		case DirectionOrder::XZY:
		{
			xPriority = 3; zPriority = 2; yPriority = 1;
			xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			break;
		}
		case DirectionOrder::YXZ:
		{
			yPriority = 3; xPriority = 1; zPriority = 2;
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			break;
		}
		case DirectionOrder::YZX:
		{
			yPriority = 3; zPriority = 2; xPriority = 1;
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			break;
		}
		case DirectionOrder::ZXY:
		{
			zPriority = 3; xPriority = 2; yPriority = 1;
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			break;
		}
		case DirectionOrder::ZYX:
		{
			zPriority = 3; yPriority = 2; xPriority = 1;
			zPriority *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
			yPriority *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
			xPriority *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
			break;
		}
		}

		if ((xPriority > yPriority) && (xPriority > zPriority) && (yPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrder::XYZ;
		}
		if ((xPriority > yPriority) && (xPriority > zPriority) && (zPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::XZY;
		}
		if ((yPriority > xPriority) && (yPriority > zPriority) && (xPriority >= zPriority))
		{
			_responseDirectionOrder = DirectionOrder::YXZ;
		}
		if ((yPriority > xPriority) && (yPriority > zPriority) && (zPriority >= xPriority))
		{
			_responseDirectionOrder = DirectionOrder::YZX;
		}
		if ((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::ZYX;
		}
		if ((zPriority > xPriority) && (zPriority > yPriority) && (xPriority >= yPriority))
		{
			_responseDirectionOrder = DirectionOrder::ZXY;
		}

		_lastCameraPosition = camera.getPosition();
	}
}