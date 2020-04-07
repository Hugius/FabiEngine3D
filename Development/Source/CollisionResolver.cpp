#include <WE3D/CollisionResolver.hpp>
#include <WE3D/Logger.hpp>

CollisionResolver::CollisionResolver(CollisionDetector& collisionDetector) :
	p_collisionDetector(collisionDetector)
{
	
}

void CollisionResolver::update(const vector<AabbEntity*> & boxes, TerrainEntityManager& terrainManager, CameraManager & camera, float delta)
{
	// Check if AABB collision is needed in the first place
	if (p_aabbResponseEnabled)
	{
		// Init
		static vec3 oldCameraPos;
		vec3 currentCameraPos = camera.getPosition();
		vec3 posDifference = oldCameraPos - currentCameraPos;
		posDifference = vec3(fabsf(posDifference.x), fabsf(posDifference.y), fabsf(posDifference.z));
		Collision collision(false, false, false);

		// Detect
		for (auto& box : boxes)
		{
			auto direction = box->getCollisionDirection();
			auto result = p_collisionDetector.check(*box, currentCameraPos, posDifference, direction);
			box->setCollisionDirection(direction);

			// If responsive to camera
			if (box->isResponsive())
			{
				collision += result;
			}
		}

		// Response
		vec3 newCameraPos = currentCameraPos;
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
	if (p_terrainResponseEnabled)
	{
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			float camX = camera.getPosition().x;
			float camY = camera.getPosition().y;
			float camZ = camera.getPosition().z;
			float targetY = terrainManager.getPixelHeight(camX, camZ) + p_cameraHeight;

			// If camera goes underground
			if (camY < targetY)
			{
				p_aboveGround = false;
				p_underGround = true;
				camera.translate(vec3(0.0f, p_cameraSpeed, 0.0f), delta);
				camY = camera.getPosition().y;

				// Check again
				if (camY > targetY)
				{
					camera.setPosition(vec3(camX, targetY, camZ));
					p_underGround = false;
				}
			}
			else if (camY > targetY)
			{
				p_aboveGround = true;
				p_underGround = false;
			}
		}
	}
}

void CollisionResolver::enableAabbResponse()
{
	p_aabbResponseEnabled = true;
}

void CollisionResolver::disableAabbResponse()
{
	p_aabbResponseEnabled = false;
}

void CollisionResolver::enableTerrainResponse(float cameraHeight, float cameraSpeed)
{
	p_terrainResponseEnabled = true;
	p_cameraHeight = cameraHeight;
	p_cameraSpeed = cameraSpeed;
}

void CollisionResolver::disableTerrainResponse()
{
	p_terrainResponseEnabled = false;
}

bool CollisionResolver::isCameraAboveGround()
{
	return p_aboveGround;
}

bool CollisionResolver::isCameraUnderGround()
{
	return p_underGround;
}