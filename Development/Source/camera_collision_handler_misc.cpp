#include "camera_collision_handler.hpp"
#include "logger.hpp"

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
						camera.setPosition(Vec3(_lastCameraPosition.x, middle.y, middle.z));
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
							camera.setPosition(Vec3(middle.x, _lastCameraPosition.y, middle.z));
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
						camera.setPosition(Vec3(middle.x, middle.y, _lastCameraPosition.z));
						return true;
					}
				}

				break;
			}
		}
	}

	return false;
}