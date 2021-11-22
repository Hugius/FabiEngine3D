#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Camera& camera);

	// VOID
	void update() override;
	void createEntity(const string& ID);

	// MISCELLANEOUS
	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();
	shared_ptr<BillboardEntity> getEntity(const string& ID);

private:
	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> _renderBuffer;
	Camera& _camera;
};