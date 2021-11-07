#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Camera& camera);

	// Voids
	void update() override;
	void createEntity(const string& ID);

	// Miscellaneous
	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();
	shared_ptr<BillboardEntity> getEntity(const string& ID);

private:
	// Miscellaneous
	const shared_ptr<RenderBuffer> _renderBuffer;
	Camera& _camera;
};