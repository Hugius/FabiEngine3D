#include "collision_resolver.hpp"
#include "logger.hpp"

CollisionResolver::CollisionResolver() :
	_cameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
{

}

void CollisionResolver::update(
	const unordered_map<string, shared_ptr<AabbEntity>>& aabbs, 
	TerrainEntityManager& terrainManager, 
	Camera& camera, CollisionDetector& collisionDetector)
{
	// Check if AABB collision is needed in the first place
	if (_isCameraAabbResponseEnabled)
	{
		// Temporary values
		static Vec3 oldCameraPosition;
		bool hasCollidedX = false;
		bool hasCollidedY = false;
		bool hasCollidedZ = false;

		// Reset collision
		for (const auto& [keyID, aabb] : aabbs)
		{
			aabb->setCollided(false);
		}

		// Detect X collision
		for (const auto& [keyID, aabb] : aabbs)
		{
			// If responsive to camera collision
			if (aabb->isCollisionResponsive() && aabb->isVisible())
			{
				// Check collision with AABB
				const Vec3 middle = camera.getPosition();
				const Vec3 middleChange = (middle - oldCameraPosition);
				auto hasCollided = collisionDetector.checkX(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

				// Update AABB
				if (hasCollided)
				{
					aabb->setCollisionDirection(Direction::X);
					aabb->setCollided(true);
				}

				// Respond to X collision
				if (_isCameraAabbResponseEnabledX && hasCollided)
				{
					camera.setPosition(Vec3(oldCameraPosition.x, camera.getPosition().y, camera.getPosition().z));
				}
			}
		}
		
		// Detect Y collision
		for (const auto& [keyID, aabb] : aabbs)
		{
			// If responsive to camera collision
			if (aabb->isCollisionResponsive() && aabb->isVisible())
			{
				// Check collision with AABB
				const Vec3 middle = camera.getPosition();
				const Vec3 middleChange = (middle - oldCameraPosition);
				auto hasCollided = collisionDetector.checkY(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

				// Update AABB
				if (hasCollided)
				{
					aabb->setCollisionDirection(Direction::Y);
					aabb->setCollided(true);
				}

				// Respond to Y collision
				if (_isCameraAabbResponseEnabledY && hasCollided)
				{
					// Terrain collision response has priority
					if (!_isCameraUnderTerrain)
					{
						camera.setPosition(Vec3(camera.getPosition().x, oldCameraPosition.y, camera.getPosition().z));
					}
				}
			}
		}

		// Detect Z collision
		for (const auto& [keyID, aabb] : aabbs)
		{
			// If responsive to camera collision
			if (aabb->isCollisionResponsive() && aabb->isVisible())
			{
				// Check collision with AABB
				const Vec3 middle = camera.getPosition();
				const Vec3 middleChange = (middle - oldCameraPosition);
				auto hasCollided = collisionDetector.checkZ(aabb->getPosition(), aabb->getSize(), middle, middleChange, _cameraBox);

				// Update AABB
				if (hasCollided)
				{
					aabb->setCollisionDirection(Direction::Z);
					aabb->setCollided(true);
				}

				// Respond to Z collision
				if (_isCameraAabbResponseEnabledZ && hasCollided)
				{
					camera.setPosition(Vec3(camera.getPosition().x, camera.getPosition().y, oldCameraPosition.z));
				}
			}
		}

		// Store old camera position
		oldCameraPosition = camera.getPosition();
	}
	
	// Check if terrain collision is needed in the first place
	_isCameraUnderTerrain = false;
	if (_isCameraTerrainResponseEnabled)
	{
		// Check if a terrain is selected
		if (terrainManager.getSelectedTerrain() != nullptr)
		{
			// Retrieve height of terrain point at camera position
			Vec3 cameraPosition = camera.getPosition();
			const float terrainX = cameraPosition.x + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float terrainZ = cameraPosition.z + (terrainManager.getSelectedTerrain()->getSize() / 2.0f);
			const float targetY = terrainManager.getPixelHeight(terrainManager.getSelectedTerrain()->getID(), terrainX, terrainZ) + _cameraTerrainHeight;

			// If camera goes underground
			if (cameraPosition.y < targetY)
			{
				_isCameraUnderTerrain = true;

				// Move camera upwards
				camera.move(Vec3(0.0f, fabsf(cameraPosition.y - targetY) * _cameraTerrainSpeed, 0.0f));
				cameraPosition.y = camera.getPosition().y;

				// Correct moved distance
				if (cameraPosition.y > targetY)
				{
					camera.setPosition(Vec3(cameraPosition.x, targetY, cameraPosition.z));
				}
			}
		}
	}
}

void CollisionResolver::setCameraBox(const Box& box)
{
	_cameraBox = box;
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