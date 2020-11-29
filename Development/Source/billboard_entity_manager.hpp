#pragma once

#include "base_entity_manager.hpp"
#include "camera_manager.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus, CameraManager& camera);
	~BillboardEntityManager() = default;

	shared_ptr<BillboardEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();

	void addBillboardEntity
	(
		const string& ID, Vec3 color,
		Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string& ID, const string& texturePath,
		Vec3 T, Vec3 R, Vec3 S,
		bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
	);

	void addBillboardEntity
	(
		const string& ID, const string& text, 
		const string& fontPath, Vec3 color,
		Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY
	);

	void update() override;

private:
	CameraManager& _camera;

	OpenGLBuffer* _openglBuffer = nullptr;

	const unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
};