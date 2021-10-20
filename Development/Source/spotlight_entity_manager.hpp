#pragma once

#include "base_entity_manager.hpp"

class SpotlightEntityManager final : public BaseEntityManager
{
public:
	SpotlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// Voids
	void createEntity(const string& ID);
	void update() override;

	// Instances
	shared_ptr<SpotlightEntity> getEntity(const string& ID);
	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();

	// Integers
	static inline const unsigned int MAX_LIGHT_COUNT = 64;
};