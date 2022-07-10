#include "camera_collision_handler.hpp"

void CameraCollisionHandler::_handleTerrainCollision()
{
	if(_terrainManager->getSelectedTerrain() != nullptr)
	{
		fvec3 cameraPosition = _camera->getPosition();

		const auto terrainX = (cameraPosition.x + (_terrainManager->getSelectedTerrain()->getSize() * 0.5f));
		const auto terrainZ = (cameraPosition.z + (_terrainManager->getSelectedTerrain()->getSize() * 0.5f));
		const auto terrainY = (_terrainManager->getTerrainPixelHeight(_terrainManager->getSelectedTerrain()->getId(), terrainX, terrainZ) + _cameraTerrainResponseHeight);

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

const bool CameraCollisionHandler::_handleAabbCollision(DirectionType direction) const
{
	for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
	{
		if(aabb->isCollisionResponsive())
		{
			switch(direction)
			{
				case DirectionType::X:
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _isInsideAabbX(aabb, middle, middleChange, _cameraBox);

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

					break;
				}
				case DirectionType::Y:
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _isInsideAabbY(aabb, middle, middleChange, _cameraBox);

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

					break;
				}
				case DirectionType::Z:
				{
					const auto middle = _camera->getPosition();
					const auto middleChange = (middle - _lastCameraPosition);
					const auto hasCollided = _isInsideAabbZ(aabb, middle, middleChange, _cameraBox);

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

					break;
				}
			}
		}
	}

	return false;
}