#include "collision_resolver.hpp"
#include "logger.hpp"

CollisionResolver::CollisionResolver(CollisionDetector& collisionDetector) :
	_collisionDetector(collisionDetector)
{
	
}

void CollisionResolver::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& boxes, 
	TerrainEntityManager& terrainManager, 
	CameraManager& camera)
{
	// Check if AABB collision is needed in the first place
	if (_aabbResponseEnabled)
	{
		// Temporary values
		static Vec3 oldCameraPos;
		Vec3 currentCameraPos = camera.getPosition();
		Vec3 posDifference = oldCameraPos - currentCameraPos;
		posDifference = Vec3(fabsf(posDifference.x), fabsf(posDifference.y), fabsf(posDifference.z));
		Collision collision(false, false, false);

		// Detect collision
		for (auto& [keyID, box] : boxes)
		{
			// If responsive to camera collision
			if (box->isResponsive() && box->isVisible())
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
		if (collision.xCollided())
		{
			newCameraPos.x = oldCameraPos.x;
		}
		if (collision.yCollided() && !_isCameraUnderTerrain) // If camera is under terrain, response cannot be blocked
		{
			newCameraPos.y = oldCameraPos.y;
		}
		if (collision.zCollided())
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
	if (_terrainResponseEnabled)
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

void CollisionResolver::enableAabbResponse(float bottom, float top, float left, float right, float front, float back)
{
	_aabbResponseEnabled = true;
	_cameraAabbBottom = bottom * 0.99f;
	_cameraAabbTop = top * 0.99f;
	_cameraAabbLeft = left * 0.99f;
	_cameraAabbRight = right * 0.99f;
	_cameraAabbFront = front * 0.99f;
	_cameraAabbBack = back * 0.99f;
}

void CollisionResolver::disableAabbResponse()
{
	_aabbResponseEnabled = false;
}

void CollisionResolver::enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_terrainResponseEnabled = true;
	_cameraTerrainHeight = cameraHeight;
	_cameraTerrainSpeed = cameraSpeed;
}

void CollisionResolver::disableTerrainResponse()
{
	_terrainResponseEnabled = false;
}

bool CollisionResolver::isCameraUnderTerrain()
{
	return _isCameraUnderTerrain;
}