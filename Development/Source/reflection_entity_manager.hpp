#pragma once

#include "base_entity_manager.hpp"

class ReflectionEntityManager final : public BaseEntityManager
{
public:
	ReflectionEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void createEntity(const string& ID);
	void update() override;

	// Miscellaneous
	shared_ptr<ReflectionEntity> getEntity(const string& ID);
	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();
};