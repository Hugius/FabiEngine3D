#include "camera_collision_responder.hpp"

using std::make_shared;

CameraCollisionResponder::CameraCollisionResponder()
{
	_cameraBox = make_shared<Box>(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void CameraCollisionResponder::inject(shared_ptr<TerrainManager> terrainManager)
{
	_terrainManager = terrainManager;
}

void CameraCollisionResponder::inject(shared_ptr<AabbManager> aabbManager)
{
	_aabbManager = aabbManager;
}

void CameraCollisionResponder::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void CameraCollisionResponder::inject(shared_ptr<CameraCollisionDetector> cameraCollisionDetector)
{
	_cameraCollisionDetector = cameraCollisionDetector;
}

void CameraCollisionResponder::setCameraBox(const shared_ptr<Box> value)
{
	_cameraBox = value;
}

void CameraCollisionResponder::setCameraAabbResponseEnabled(bool x, bool y, bool z)
{
	_isCameraAabbResponseEnabledX = x;
	_isCameraAabbResponseEnabledY = y;
	_isCameraAabbResponseEnabledZ = z;
}

void CameraCollisionResponder::setCameraTerrainResponseEnabled(bool value)
{
	_isCameraTerrainResponseEnabled = value;
}

void CameraCollisionResponder::setCameraTerrainResponseHeight(float value)
{
	_cameraTerrainResponseHeight = value;
}

void CameraCollisionResponder::setCameraTerrainResponseSpeed(float value)
{
	_cameraTerrainResponseSpeed = value;
}

const float CameraCollisionResponder::getCameraTerrainResponseHeight() const
{
	return _cameraTerrainResponseHeight;
}

const float CameraCollisionResponder::getCameraTerrainResponseSpeed() const
{
	return _cameraTerrainResponseSpeed;
}

const bool CameraCollisionResponder::isCameraUnderTerrain() const
{
	return _isCameraUnderTerrain;
}

const bool CameraCollisionResponder::isCameraAabbResponseEnabledX() const
{
	return _isCameraAabbResponseEnabledX;
}

const bool CameraCollisionResponder::isCameraAabbResponseEnabledY() const
{
	return _isCameraAabbResponseEnabledY;
}

const bool CameraCollisionResponder::isCameraAabbResponseEnabledZ() const
{
	return _isCameraAabbResponseEnabledZ;
}

const bool CameraCollisionResponder::isCameraTerrainResponseEnabled() const
{
	return _isCameraTerrainResponseEnabled;
}

const bool CameraCollisionResponder::_handleCollision(DirectionType direction) const
{
	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		switch(direction)
		{
			case DirectionType::X:
			{
				if(aabb->isCollisionResponsive())
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _cameraCollisionDetector->checkX(aabb->getBasePosition(), aabb->getBaseSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(DirectionType::X);
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
			case DirectionType::Y:
			{
				if(aabb->isCollisionResponsive())
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _cameraCollisionDetector->checkY(aabb->getBasePosition(), aabb->getBaseSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(DirectionType::Y);
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
			case DirectionType::Z:
			{
				if(aabb->isCollisionResponsive())
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _cameraCollisionDetector->checkZ(aabb->getBasePosition(), aabb->getBaseSize(), middle, middleChange, _cameraBox);

					if(hasCollided)
					{
						aabb->setCollisionDirection(DirectionType::Z);
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