#include "collision_resolver.hpp"
#include "logger.hpp"

CollisionResolver::CollisionResolver(CollisionDetector& collisionDetector) :
	_collisionDetector(collisionDetector)
{
	
}

void CollisionResolver::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& boxes, 
	TerrainEntityManager& terrainManager, 
	CameraManager & camera)
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
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			float camX = camera.getPosition().x;
			float camY = camera.getPosition().y;
			float camZ = camera.getPosition().z;
			float targetY = terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), camX, camZ) + _cameraHeight;

			// If camera goes underground
			if (camY < targetY)
			{
				_aboveGround = false;
				_underGround = true;
				camera.translate(Vec3(0.0f, _cameraSpeed, 0.0f));
				camY = camera.getPosition().y;

				// Check again
				if (camY > targetY)
				{
					camera.setPosition(Vec3(camX, targetY, camZ));
					_underGround = false;
				}
			}
			else if (camY > targetY)
			{
				_aboveGround = true;
				_underGround = false;
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

bool CollisionResolver::isCameraAboveGround()
{
	return _aboveGround;
}

bool CollisionResolver::isCameraUnderGround()
{
	return _underGround;
}