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
				auto result = _collisionDetector.check(*box, currentCameraPos, posDifference, direction);
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
		if (collision.yCollided())
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
	if (_terrainResponseEnabled)
	{
		// Check if a terrain is selected
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			// Retrieve height of terrain point at camera position
			Vec3 camPos = camera.getPosition();
			const float terrainX = camPos.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float terrainZ = camPos.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float targetY = terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraHeight;

			// If camera goes underground
			if (camPos.y < targetY)
			{
				_isCameraUnderTerrain = true;

				// Move camera upwards
				camera.translate(Vec3(0.0f, fabsf(camPos.y - targetY) * _cameraSpeed, 0.0f));
				camPos.y = camera.getPosition().y;

				// Correct moved distance
				if (camPos.y > targetY)
				{
					camera.setPosition(Vec3(camPos.x, targetY, camPos.z));
				}
			}
			else
			{
				_isCameraUnderTerrain = false;
			}
		}
	}
}

void CollisionResolver::enableAabbResponse()
{
	_aabbResponseEnabled = true;
}

void CollisionResolver::disableAabbResponse()
{
	_aabbResponseEnabled = false;
}

void CollisionResolver::enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	_terrainResponseEnabled = true;
	_cameraHeight = cameraHeight;
	_cameraSpeed = cameraSpeed;
}

void CollisionResolver::disableTerrainResponse()
{
	_terrainResponseEnabled = false;
}

bool CollisionResolver::isCameraUnderTerrain()
{
	return _isCameraUnderTerrain;
}