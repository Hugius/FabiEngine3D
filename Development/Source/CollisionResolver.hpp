#pragma once

#include "CollisionDetector.hpp"
#include "AabbEntity.hpp"
#include "CameraManager.hpp"
#include "TerrainEntityManager.hpp"

class CollisionResolver
{
public:
	CollisionResolver(CollisionDetector& collisionDetector);
	virtual ~CollisionResolver() = default;
	
	void update(const vector<AabbEntity*> & boxes, TerrainEntityManager& terrainManager, CameraManager & camera, float delta);
	void enableAabbResponse();
	void disableAabbResponse();
	void enableTerrainResponse(float cameraHeight, float cameraSpeed);
	void disableTerrainResponse();

	bool isCameraAboveGround();
	bool isCameraUnderGround();

private:
	CollisionDetector& p_collisionDetector;

	float p_cameraHeight = 0.0f;
	float p_cameraSpeed = 0.0f;

	bool p_aabbResponseEnabled    = false;
	bool p_terrainResponseEnabled = false;
	bool p_aboveGround			  = false;
	bool p_underGround			  = false;
};