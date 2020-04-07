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
	CollisionDetector& _collisionDetector;

	float _cameraHeight = 0.0f;
	float _cameraSpeed = 0.0f;

	bool _aabbResponseEnabled    = false;
	bool _terrainResponseEnabled = false;
	bool _aboveGround			  = false;
	bool _underGround			  = false;
};