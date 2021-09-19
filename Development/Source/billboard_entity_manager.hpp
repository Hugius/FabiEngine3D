#pragma once

#include "base_entity_manager.hpp"
#include "camera.hpp"

class BillboardEntityManager final : public BaseEntityManager
{
public:
	BillboardEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus, Camera& camera);

	shared_ptr<BillboardEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<BillboardEntity>>& getEntities();

	void createEntity(const string& ID);

	void update() override;

private:
	Camera& _camera;

	const shared_ptr<RenderBuffer> _renderBuffer;
};