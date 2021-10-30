#include "camera_collision_handler.hpp"

#include <iostream>

void CameraCollisionHandler::update(const unordered_map<string, shared_ptr<AabbEntity>>& aabbs,
									TerrainEntityManager& terrainManager, Camera& camera, Raycaster& raycaster)
{
	// Check if terrain collision is needed in the first place
	_isCameraUnderTerrain = false;
	if(_isCameraTerrainResponseEnabled)
	{
		// Check if a terrain is selected
		if(terrainManager.getSelectedTerrain() != nullptr)
		{
			// Retrieve height of terrain point at camera position
			Vec3 cameraPosition = camera.getPosition();
			const float terrainX = (cameraPosition.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f));
			const float terrainZ = (cameraPosition.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f));
			const float terrainY = (terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraTerrainHeight);

			// If camera goes underground
			if(cameraPosition.y < terrainY)
			{
				// Camera is now under terrain
				_isCameraUnderTerrain = true;

				// Move camera upwards
				camera.move(Vec3(0.0f, fabsf(cameraPosition.y - terrainY) * _cameraTerrainSpeed, 0.0f));
				cameraPosition.y = camera.getPosition().y;

				// Correct moved distance
				if(cameraPosition.y > terrainY)
				{
					camera.setPosition(Vec3(cameraPosition.x, terrainY, cameraPosition.z));
				}
			}
		}
	}

	// Check if AABB collision is needed in the first place
	if(_isCameraAabbResponseEnabled)
	{
		// Temporary values
		unsigned int xPriority = 0;
		unsigned int yPriority = 0;
		unsigned int zPriority = 0;

		// Reset collision
		for(const auto& [keyID, aabb] : aabbs)
		{
			aabb->setCollided(false);
		}

		// Handle collision
		switch(_responseDirectionOrder)
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

		// Rearrange collision order
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

		std::cout << static_cast<int>(_responseDirectionOrder) << std::endl;

		// Store last camera position
		_lastCameraPosition = camera.getPosition();
	}
}