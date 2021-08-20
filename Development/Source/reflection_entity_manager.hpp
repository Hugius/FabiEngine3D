#pragma once

#include "base_entity_manager.hpp"

class ReflectionEntityManager final : public BaseEntityManager
{
public:
	ReflectionEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<ReflectionEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<ReflectionEntity>>& getEntities();

	void createEntity(const string& ID);

	void update() override {};
};