#pragma once
#include "base_entity_manager.hpp"
#include "camera_manager.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus, CameraManager& camera);
	~BillboardEntityManager() = default;

	BillboardEntity * getEntity(const string & ID) override;

	const vector<BillboardEntity*> getEntities();

	void addBillboardEntity
	(
		const string& ID, vec3 color,
		vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string& ID, const string& texturePath,
		vec3 T, vec3 R, vec3 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
	);

	void addBillboardEntity
	(
		const string & ID, const string & text, 
		const string & fontPath, vec3 color,
		vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
	);

	void update() override;

private:
	CameraManager& _camera;
};