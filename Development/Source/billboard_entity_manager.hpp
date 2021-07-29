#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus, Camera& camera);

	shared_ptr<BillboardEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();

	void addBillboardEntity
	(
		const string& ID, Vec3 color,
		Vec3 position, Vec3 rotation, Vec3 size, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string& ID, const string& diffuseMapPath,
		Vec3 position, Vec3 rotation, Vec3 size,
		bool transparent, bool facingCameraX, bool facingCameraY
	);

	void addBillboardEntity
	(
		const string& ID, const string& textContent,
		const string& fontPath, Vec3 color,
		Vec3 position, Vec3 rotation, Vec3 size, bool facingCameraX, bool facingCameraY
	);

	void update() override;

private:
	Camera& _camera;

	RenderBuffer* _renderBuffer = nullptr;

	const unordered_map<string, shared_ptr<BillboardEntity>> _billboardEntities;
};