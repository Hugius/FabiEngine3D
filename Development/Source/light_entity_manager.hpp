#pragma once

#include "base_entity_manager.hpp"

class LightEntityManager final : public BaseEntityManager
{
public:
	LightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void createEntity(const string& ID);
	void update() override;

	// Instances
	shared_ptr<LightEntity> getEntity(const string& ID);
	const unordered_map<string, shared_ptr<LightEntity>>& getEntities();

	// Integers
	static inline const unsigned int MAX_LIGHT_COUNT = 128;
};