#pragma once

#include "base_entity_manager.hpp"

class LightEntityManager final : public BaseEntityManager
{
public:
	LightEntityManager(MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus);

	shared_ptr<LightEntity> getEntity(const string& ID);

	const unordered_map<string, shared_ptr<LightEntity>>& getEntities();

	void addLightEntity(const string& ID, Vec3 position, Vec3 radius, Vec3 color, float intensity);

	void update() override;
};