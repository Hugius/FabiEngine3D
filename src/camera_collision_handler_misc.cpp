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

const bool CameraCollisionHandler::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabled() const
{
	return _isCameraAabbResponseEnabled;
}

const bool CameraCollisionHandler::isCameraTerrainResponseEnabled() const
{
	return _isCameraTerrainResponseEnabled;
}

const bool CameraCollisionHandler::_handleCollision(Direction direction, const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, Camera& camera) const
{
	for(const auto& [keyID, aabb] : aabbs)
	{
		switch(direction)
		{
			case Direction::X:
			{
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					const fvec3 middle = camera.getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkX(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::X);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledX && hasCollided)
					{
						camera.setPosition(fvec3(_lastCameraPosition.x, middle.y, middle.z));
						return true;
					}
				}

				break;
			}
			case Direction::Y:
			{
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					const fvec3 middle = camera.getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkY(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Y);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledY && hasCollided)
					{
						if(!_isCameraUnderTerrain)
						{
							camera.setPosition(fvec3(middle.x, _lastCameraPosition.y, middle.z));
							return true;
						}
					}
				}

				break;
			}
			case Direction::Z:
			{
				if(aabb->isCollisionResponsive() && aabb->isVisible())
				{
					const fvec3 middle = camera.getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _collisionDetector.checkZ(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Z);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledZ && hasCollided)
					{
						camera.setPosition(fvec3(middle.x, middle.y, _lastCameraPosition.z));
						return true;
					}
				}

				break;
			}
		}
	}

	return false;
}