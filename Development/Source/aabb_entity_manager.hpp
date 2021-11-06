#pragma once

#include "base_entity_manager.hpp"

class AabbEntityManager final : public BaseEntityManager
{
public:
	AabbEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void update() override;
	void createEntity(const string& ID);
	void update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities, const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities);

	// Miscellaneous
	const unordered_map<string, shared_ptr<AabbEntity>>& getEntities();
	shared_ptr<AabbEntity> getEntity(const string& ID);

private:
	// Miscellaneous
	const shared_ptr<RenderBuffer> _renderBuffer;
};