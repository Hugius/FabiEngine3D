#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus, Camera& camera);
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
		bool transparent, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string& ID, const string& text, 
		const string& fontPath, Vec3 color,
		Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY
	);

	void update() override;

private:
	Camera& _camera;

	RenderBuffer* _renderBuffer = nullptr;

	const unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
};