#include "camera_collision_handler.hpp"
#include "logger.hpp"

void CameraCollisionHandler::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& aabbs,
	TerrainEntityManager& terrainManager,
	Camera& camera, Raycaster& raycaster)
{
	// Check if AABB collision is needed in the first place
	if(_isCameraAabbResponseEnabled)
	{
		// Temporary values
		bool hasCollidedX = false;
		bool hasCollidedY = false;
		bool hasCollidedZ = false;

		// Reset collision
		for(const auto& [keyID, aabb] : aabbs)
		{
			aabb->setCollided(false);
		}

		// Handle collision
		switch(_priorityCollisionDirection)
		{
			case Direction::X:
			{
				bool hasCollidedX = _handleCollision(Direction::X, aabbs, camera);
				bool hasCollidedY = _handleCollision(Direction::Y, aabbs, camera);
				bool hasCollidedZ = _handleCollision(Direction::Z, aabbs, camera);

				if(!hasCollidedX)
				{
					if(hasCollidedY)
					{
						_priorityCollisionDirection = Direction::Y;
					}
					if(hasCollidedZ)
					{
						_priorityCollisionDirection = Direction::Y;
					}
				}

				break;
			}
			case Direction::Y:
			{
				bool hasCollidedY = _handleCollision(Direction::Y, aabbs, camera);
				bool hasCollidedX = _handleCollision(Direction::X, aabbs, camera);
				bool hasCollidedZ = _handleCollision(Direction::Z, aabbs, camera);

				if(!hasCollidedY)
				{
					if(hasCollidedX)
					{
						_priorityCollisionDirection = Direction::X;
					}
					if(hasCollidedZ)
					{
						_priorityCollisionDirection = Direction::Z;
					}
				}

				break;
			}
			case Direction::Z:
			{
				bool hasCollidedZ = _handleCollision(Direction::Z, aabbs, camera);
				bool hasCollidedX = _handleCollision(Direction::X, aabbs, camera);
				bool hasCollidedY = _handleCollision(Direction::Y, aabbs, camera);

				if(!hasCollidedZ)
				{
					if(hasCollidedX)
					{
						_priorityCollisionDirection = Direction::X;
					}
					if(hasCollidedY)
					{
						_priorityCollisionDirection = Direction::Y;
					}
				}

				break;
			}
		}

		// Store last camera position
		_lastCameraPosition = camera.getPosition();
	}

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