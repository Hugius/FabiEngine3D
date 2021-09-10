#include "collision_resolver.hpp"
#include "logger.hpp"

using std::max;

void CollisionResolver::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, 
	TerrainEntityManager& terrainManager, 
	Camera& camera, CollisionDetector& collisionDetector)
{
	// Check if AABB collision is needed in the first place
	if (_isCameraAabbResponseEnabled)
	{
		// Temporary values
		static Vec3 oldCameraPos;
		Vec3 middlePosition = camera.getPosition();
		Vec3 middleChange = (middlePosition - oldCameraPos);
		Collision collision(false, false, false);

		// Detect collision
		for (const auto& [keyID, aabb] : aabbs)
		{
			// If responsive to camera collision
			if (aabb->isCollisionResponsive() && aabb->isVisible())
			{
				// Check collision with AABB
				auto result = collisionDetector.check(aabb->getPosition(), aabb->getSize(), middlePosition,
					_cameraAabbBottom, _cameraAabbTop, _cameraAabbLeft, _cameraAabbRight, _cameraAabbFront, _cameraAabbBack, 
					middleChange, aabb->hasCollided());

				// Set direction
				if (result.xCollided())
				{
					aabb->setCollisionDirection(Direction::X);
					aabb->setCollided(true);
				}
				else if (result.yCollided())
				{
					aabb->setCollisionDirection(Direction::Y);
					aabb->setCollided(true);
				}
				else if (result.zCollided())
				{
					aabb->setCollisionDirection(Direction::Z);
					aabb->setCollided(true);
				}
				else
				{
					aabb->setCollided(false);
				}

				// Add to total collision
				collision += result;
			}
		}

		// Respond to collision
		Vec3 newCameraPos = middlePosition;
		if (collision.xCollided() && _isCameraAabbResponseEnabledX)
		{
			newCameraPos.x = oldCameraPos.x;
		}
		if (collision.yCollided() && _isCameraAabbResponseEnabledY)
		{
			// If camera is under terrain, response cannot be blocked
			if (!_isCameraUnderTerrain)
			{
				newCameraPos.y = oldCameraPos.y;
			}
		}
		if (collision.zCollided() && _isCameraAabbResponseEnabledZ)
		{
			newCameraPos.z = oldCameraPos.z;
		}

		// Set new camera position
		camera.setPosition(newCameraPos);

		// Store old camera position
		oldCameraPos = camera.getPosition();
	}
	
	// Check if terrain collision is needed in the first place
	_isCameraUnderTerrain = false;
	if (_isCameraTerrainResponseEnabled)
	{
		// Check if a terrain is selected
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			// Retrieve height of terrain point at camera position
			Vec3 camPos = camera.getPosition();
			const float terrainX = camPos.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float terrainZ = camPos.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float targetY = terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraTerrainHeight;

			// If camera goes underground
			if (camPos.y < targetY)
			{
				_isCameraUnderTerrain = true;

				// Move camera upwards
				camera.move(Vec3(0.0f, fabsf(camPos.y - targetY) * _cameraTerrainSpeed, 0.0f));
				camPos.y = camera.getPosition().y;

				// Correct moved distance
				if (camPos.y > targetY)
				{
					camera.setPosition(Vec3(camPos.x, targetY, camPos.z));
				}
			}
		}
	}
}

void CollisionResolver::setCameraBoxSize(float bottom, float top, float left, float right, float front, float back)
{
	_cameraAabbBottom = max(0.0f, (bottom * 0.99f));
	_cameraAabbTop = max(0.0f, (top * 0.99f));
	_cameraAabbLeft = max(0.0f, (left * 0.99f));
	_cameraAabbRight = max(0.0f, (right * 0.99f));
	_cameraAabbFront = max(0.0f, (front * 0.99f));
	_cameraAabbBack = max(0.0f, (back * 0.99f));
}

void CollisionResolver::enableCameraAabbResponse(bool x, bool y, bool z)
{
	if (_isCameraAabbResponseEnabled)
	{
		Logger::throwError("CollisionResolver::enableCameraAabbResponse");
	}

	_isCameraAabbResponseEnabled = true;
	_isCameraAabbResponseEnabledX = x;
	_isCameraAabbResponseEnabledY = y;
	_isCameraAabbResponseEnabledZ = z;
}

void CollisionResolver::disableCameraAabbResponse()
{
	if (!_isCameraAabbResponseEnabled)
	{
		Logger::throwError("CollisionResolver::disableCameraAabbResponse");
	}

	_isCameraAabbResponseEnabled = false;
	_isCameraAabbResponseEnabledX = false;
	_isCameraAabbResponseEnabledY = false;
	_isCameraAabbResponseEnabledZ = false;
}

void CollisionResolver::enableCameraTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if (_isCameraTerrainResponseEnabled)
	{
		Logger::throwError("CollisionResolver::enableCameraTerrainResponse");
	}

	_isCameraTerrainResponseEnabled = true;
	_cameraTerrainHeight = cameraHeight;
	_cameraTerrainSpeed = cameraSpeed;
}

void CollisionResolver::disableCameraTerrainResponse()
{
	if (!_isCameraTerrainResponseEnabled)
	{
		Logger::throwError("CollisionResolver::disableCameraTerrainResponse");
	}

	_isCameraTerrainResponseEnabled = false;
}

bool CollisionResolver::isCameraUnderTerrain()
{
	return _isCameraUnderTerrain;
}

bool CollisionResolver::isCameraAabbResponseEnabled()
{
	return _isCameraAabbResponseEnabled;
}

bool CollisionResolver::isCameraTerrainResponseEnabled()
{
	return _isCameraTerrainResponseEnabled;
}