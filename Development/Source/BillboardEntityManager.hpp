#pragma once
#include "EntityManager.hpp"

class BillboardEntityManager final :  public EntityManager
{
public:
	BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus);
	~BillboardEntityManager() = default;

	BillboardEntity * getEntity(const string & ID) override;

	const vector<BillboardEntity*> getEntities();

	void addBillboardEntity
	(
		const string & ID, const string & text, 
		const string & fontPath, vec3 color,
		vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string & ID, const string & textureName,
		vec3 T, vec3 R, vec3 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
	);

	void update(float delta) override;
};