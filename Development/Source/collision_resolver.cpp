#include "collision_resolver.hpp"
#include "logger.hpp"

CollisionResolver::CollisionResolver(CollisionDetector& collisionDetector) :
	_collisionDetector(collisionDetector)
{
	
}

void CollisionResolver::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& boxes, 
	TerrainEntityManager& terrainManager, 
	Camera& camera)
{
	// Check if AABB collision is needed in the first place
	if (_isCameraResponseEnabled)
	{
		// Temporary values
		static Vec3 oldCameraPos;
		Vec3 currentCameraPos = camera.getPosition();
		Vec3 posDifference = oldCameraPos - currentCameraPos;
		posDifference = Vec3(fabsf(posDifference.x), fabsf(posDifference.y), fabsf(posDifference.z));
		Collision collision(false, false, false);

		// Detect collision
		for (const auto& [keyID, box] : boxes)
		{
			// If responsive to camera collision
			if (box->isCollisionResponsive() && box->isVisible())
			{
				auto direction = box->getCollisionDirection();
				auto result = _collisionDetector.check(*box, currentCameraPos, _cameraAabbBottom, _cameraAabbTop, 
					_cameraAabbLeft, _cameraAabbRight, _cameraAabbFront, _cameraAabbBack, posDifference, direction);
				box->setCollisionDirection(direction);
				collision += result;
			}
		}

		// Respond to collision
		Vec3 newCameraPos = currentCameraPos;
		if (collision.xCollided() && _isCameraResponseEnabledX)
		{
			newCameraPos.x = oldCameraPos.x;
		}
		if (collision.yCollided() && _isCameraResponseEnabledY)
		{
			// If camera is under terrain, response cannot be blocked
			if (!_isCameraUnderTerrain)
			{
				newCameraPos.y = oldCameraPos.y;
			}
		}
		if (collision.zCollided() && _isCameraResponseEnabledZ)
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
	if (_isTerrainResponseEnabled)
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
				camera.translate(Vec3(0.0f, fabsf(camPos.y - targetY) * _cameraTerrainSpeed, 0.0f));
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
	_cameraAabbBottom = bottom * 0.99f;
	_cameraAabbTop = top * 0.99f;
	_cameraAabbLeft = left * 0.99f;
	_cameraAabbRight = right * 0.99f;
	_cameraAabbFront = front * 0.99f;
	_cameraAabbBack = back * 0.99f;
}

void CollisionResolver::enableCameraResponse(bool x, bool y, bool z)
{
	if (_isCameraResponseEnabled)
	{
		Logger::throwWarning("Tried to enable camera response: already enabled!");
	}
	else
	{
		_isCameraResponseEnabled = true;
		_isCameraResponseEnabledX = x;
		_isCameraResponseEnabledY = y;
		_isCameraResponseEnabledZ = z;
	}
}

void CollisionResolver::disableAabbResponse()
{
	if (_isCameraResponseEnabled)
	{
		_isCameraResponseEnabled = false;
		_isCameraResponseEnabledX = false;
		_isCameraResponseEnabledY = false;
		_isCameraResponseEnabledZ = false;
	}
	else
	{
		Logger::throwWarning("Tried to disable camera response: not enabled!");
	}
}

void CollisionResolver::enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	if (_isTerrainResponseEnabled)
	{
		Logger::throwWarning("Tried to enable terrain response: already enabled!");
	}
	else
	{
		_isTerrainResponseEnabled = true;
		_cameraTerrainHeight = cameraHeight;
		_cameraTerrainSpeed = cameraSpeed;
	}
}

void CollisionResolver::disableTerrainResponse()
{
	if (_isTerrainResponseEnabled)
	{
		_isTerrainResponseEnabled = false;
	}
	else
	{
		Logger::throwWarning("Tried to disable terrain response: not enabled!");
	}
}

bool CollisionResolver::isCameraUnderTerrain()
{
	return _isCameraUnderTerrain;
}

bool CollisionResolver::isCameraResponseEnabled()
{
	return _isCameraResponseEnabled;
}

bool CollisionResolver::isTerrainResponseEnabled()
{
	return _isTerrainResponseEnabled;
}