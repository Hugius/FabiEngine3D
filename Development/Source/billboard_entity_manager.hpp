#pragma once

#include "base_entity_manager.hpp"
#include "camera_manager.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus, CameraManager& camera);
	~BillboardEntityManager() = default;

	shared_ptr<BillboardEntity> getEntity(const string& ID);

	const vector<shared_ptr<BillboardEntity>> getEntities();

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
		const string& ID, const string& text, 
		const string& fontPath, vec3 color,
		vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
	);

	void update() override;

private:
	CameraManager& _camera;

	OpenGLBuffer* _openglBuffer = nullptr;

	vector<shared_ptr<BillboardEntity>> _billboardEntities;
};