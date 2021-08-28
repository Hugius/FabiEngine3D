#pragma once

#include "base_entity_manager.hpp"

class AabbEntityManager final :  public BaseEntityManager
{
public:
	AabbEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<AabbEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<AabbEntity>>& getEntities();

	void createEntity(const string& ID);
	void update() override;
	void update(const unordered_map<string, shared_ptr<ModelEntity>>& modelEntities, const unordered_map<string, shared_ptr<BillboardEntity>>& billboardEntities);

private:
	const shared_ptr<RenderBuffer> _renderBuffer;
};