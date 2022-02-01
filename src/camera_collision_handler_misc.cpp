#include "camera_collision_handler.hpp"
#include "logger.hpp"

void CameraCollisionHandler::inject(shared_ptr<TerrainEntityManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void CameraCollisionHandler::inject(shared_ptr<AabbEntityManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void CameraCollisionHandler::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void CameraCollisionHandler::inject(shared_ptr<CameraCollisionDetector> cameraCollisionDetector)
{
	_cameraCollisionDetector = cameraCollisionDetector;
}

void CameraCollisionHandler::setCameraBox(const Box& value)
{
	_cameraBox = value;
}

void CameraCollisionHandler::setCameraAabbResponseEnabled(bool x, bool y, bool z)
{
	_isCameraAabbResponseEnabledX = x;
	_isCameraAabbResponseEnabledY = y;
	_isCameraAabbResponseEnabledZ = z;
}

void CameraCollisionHandler::setCameraTerrainResponseEnabled(bool value)
{
	_isCameraTerrainResponseEnabled = value;
}

void CameraCollisionHandler::setCameraTerrainResponseHeight(float value)
{
	_cameraTerrainResponseHeight = value;
}

void CameraCollisionHandler::setCameraTerrainResponseSpeed(float value)
{
	_cameraTerrainResponseSpeed = value;
}

const float CameraCollisionHandler::getCameraTerrainResponseHeight() const
{
	return _cameraTerrainResponseHeight;
}

const float CameraCollisionHandler::getCameraTerrainResponseSpeed() const
{
	return _cameraTerrainResponseSpeed;
}

const bool CameraCollisionHandler::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledX() const
{
	return _isCameraAabbResponseEnabledX;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledY() const
{
	return _isCameraAabbResponseEnabledY;
}

const bool CameraCollisionHandler::isCameraAabbResponseEnabledZ() const
{
	return _isCameraAabbResponseEnabledZ;
}

const bool CameraCollisionHandler::isCameraTerrainResponseEnabled() const
{
	return _isCameraTerrainResponseEnabled;
}

const bool CameraCollisionHandler::_handleCollision(Direction direction) const
{
	for(const auto& [key, aabb] : _aabbManager->getEntities())
	{
		switch(direction)
		{
			case Direction::X:
			{
				if(aabb->isCollisionResponsive())
				{
					const fvec3 middle = _camera->getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _cameraCollisionDetector->checkX(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::X);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledX && hasCollided)
					{
						_camera->setPosition(fvec3(_lastCameraPosition.x, middle.y, middle.z));
						return true;
					}
				}

				break;
			}
			case Direction::Y:
			{
				if(aabb->isCollisionResponsive())
				{
					const fvec3 middle = _camera->getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _cameraCollisionDetector->checkY(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Y);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledY && hasCollided)
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
			case Direction::Z:
			{
				if(aabb->isCollisionResponsive())
				{
					const fvec3 middle = _camera->getPosition();
					const fvec3 middleChange = (middle - _lastCameraPosition);
					auto hasCollided = _cameraCollisionDetector->checkZ(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(Direction::Z);
						aabb->setCollided(true);
					}

					if(_isCameraAabbResponseEnabledZ && hasCollided)
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