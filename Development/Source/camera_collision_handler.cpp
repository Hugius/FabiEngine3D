#include "camera_collision_handler.hpp"
#include "logger.hpp"

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
			const float terrainX = cameraPosition.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float terrainZ = cameraPosition.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float targetY = terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraTerrainHeight;

			// If camera goes underground
			if(cameraPosition.y < targetY)
			{
				// Camera is now under terrain
				_isCameraUnderTerrain = true;

				// Move camera upwards
				camera.move(Vec3(0.0f, fabsf(cameraPosition.y - targetY) * _cameraTerrainSpeed, 0.0f));
				cameraPosition.y = camera.getPosition().y;

				// Correct moved distance
				if(cameraPosition.y > targetY)
				{
					camera.setPosition(Vec3(cameraPosition.x, targetY, cameraPosition.z));
				}
			}
		}
	}

	// Check if AABB collision is needed in the first place
	if(_isCameraAabbResponseEnabled)
	{
		// Temporary values
		unsigned int x = 0;
		unsigned int y = 0;
		unsigned int z = 0;

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
				x = 3; y = 2; z = 1;
				x *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				break;
			}
			case DirectionOrder::XZY:
			{
				x = 3; z = 2; y = 1;
				x *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				break;
			}
			case DirectionOrder::YXZ:
			{
				y = 3; x = 1; z = 2;
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				x *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				break;
			}
			case DirectionOrder::YZX:
			{
				y = 3; z = 2; x = 1;
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				z *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				break;
			}
			case DirectionOrder::ZXY:
			{
				z = 3; x = 2; y = 1;
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				x *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				break;
			}
			case DirectionOrder::ZYX:
			{
				z = 3; y = 2; x = 1;
				z *= static_cast<unsigned int>(_handleCollision(Direction::Z, aabbs, camera));
				y *= static_cast<unsigned int>(_handleCollision(Direction::Y, aabbs, camera));
				x *= static_cast<unsigned int>(_handleCollision(Direction::X, aabbs, camera));
				break;
			}
		}

		// Rearrange collision order
		if(x > y && x > z && y > z)
		{
			_responseDirectionOrder = DirectionOrder::XYZ;
		}
		if(x > y && x > z && z > y)
		{
			_responseDirectionOrder = DirectionOrder::XZY;
		}
		if(y > x && y > z && x > z)
		{
			_responseDirectionOrder = DirectionOrder::YXZ;
		}
		if(y > x && y > z && z > x)
		{
			_responseDirectionOrder = DirectionOrder::YZX;
		}
		if(z > x && z > y && x > y)
		{
			_responseDirectionOrder = DirectionOrder::ZYX;
		}
		if(z > x && z > y && x > y)
		{
			_responseDirectionOrder = DirectionOrder::ZXY;
		}

		// Store last camera position
		_lastCameraPosition = camera.getPosition();
	}
}

void CameraCollisionHandler::setCameraBox(const Box& box)
{
	_cameraBox = box;
}

void CameraCollisionHandler::enableCameraAabbResponse(bool x, bool y, bool z)
{
	if(_isCameraAabbResponseEnabled)
	{
		Logger::throwError("CollisionResolver::enableCameraAabbResponse");
	}

	_isCameraAabbResponseEnabled = true;
	_isCameraAabbResponseEnabledX = x;
	_isCameraAabbResponseEnabledY = y;
	_isCameraAabbResponseEnabledZ = z;
}

void CameraCollisionHandler::disableCameraAabbResponse()
{
	if(!_isCameraAabbResponseEnabled)
	{
		Logger::throwError("CollisionResolver::disableCameraAabbResponse");
	}

	_isCameraAabbResponseEnabled = false;
	_isCameraAabbResponseEnabledX = false;
	_isCameraAabbResponseEnabledY = false;
	_isCameraAabbResponseEnabledZ = false;
}

void CameraCollisionHandler::enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if(_isCameraTerrainResponseEnabled)
	{
		Logger::throwError("CollisionResolver::enableCameraTerrainResponse");
	}

	_isCameraTerrainResponseEnabled = true;
	_cameraTerrainHeight = cameraHeight;
	_cameraTerrainSpeed = cameraSpeed;
}

void CameraCollisionHandler::disableCameraTerrainResponse()
{
	if(!_isCameraTerrainResponseEnabled)
	{
		Logger::throwError("CollisionResolver::disableCameraTerrainResponse");
	}

	_isCameraTerrainResponseEnabled = false;
}

bool CameraCollisionHandler::isCameraUnderTerrain()
{
	return _isCameraUnderTerrain;
}

bool CameraCollisionHandler::isCameraAabbResponseEnabled()
{
	return _isCameraAabbResponseEnabled;
}

bool CameraCollisionHandler::isCameraTerrainResponseEnabled()
{
	return _isCameraTerrainResponseEnabled;
}

bool CameraCollisionHandler::_handleCollision(Direction direction, const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, Camera& camera)
{
	for(const auto& [keyID, aabb] : aabbs)
	{
		switch(direction)
		{
			case Direction::X:
			{
				// If responsive to camera collision
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					// Check collision with AABB
					const Vec3 middle = camera.getPosition();
					const Vec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkX(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					// Update AABB
					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::X);
						aabb->setCollided(true);
					}

					// Respond to X collision
					if(_isCameraAabbResponseEnabledX && hasCollided)
					{
						camera.setPosition(Vec3(_lastCameraPosition.x, camera.getPosition().y, camera.getPosition().z));
						return true;
					}
				}

				break;
			}
			case Direction::Y:
			{
				// If responsive to camera collision
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					// Check collision with AABB
					const Vec3 middle = camera.getPosition();
					const Vec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkY(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					// Update AABB
					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Y);
						aabb->setCollided(true);
					}

					// Respond to Y collision
					if(_isCameraAabbResponseEnabledY && hasCollided)
					{
						// Terrain collision response has priority
						if(!_isCameraUnderTerrain)
						{
							camera.setPosition(Vec3(camera.getPosition().x, _lastCameraPosition.y, camera.getPosition().z));
							return true;
						}
					}
				}

				break;
			}
			case Direction::Z:
			{
				// If responsive to camera collision
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					// Check collision with AABB
					const Vec3 middle = camera.getPosition();
					const Vec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkZ(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					// Update AABB
					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Z);
						aabb->setCollided(true);
					}

					// Respond to Z collision
					if(_isCameraAabbResponseEnabledZ && hasCollided)
					{
						camera.setPosition(Vec3(camera.getPosition().x, camera.getPosition().y, _lastCameraPosition.z));
						return true;
					}
				}

				break;
			}
		}
	}

	return false;
}