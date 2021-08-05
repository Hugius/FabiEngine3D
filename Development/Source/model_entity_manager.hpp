#pragma once

#include "base_entity_manager.hpp"

class ModelEntityManager final : public BaseEntityManager
{
public:
	ModelEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<ModelEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<ModelEntity>>& getEntities();

	void createEntity(const string& ID, const string& meshPath);
	void setLodDistance(float distance);
	void update() override;

	float getLodDistance();

private:
	float _lodDistance = 0.0f;
};