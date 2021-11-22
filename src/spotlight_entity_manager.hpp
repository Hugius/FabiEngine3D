#pragma once

#include "base_entity_manager.hpp"

class SpotlightEntityManager final : public BaseEntityManager
{
public:
	SpotlightEntityManager(MeshLoader& meshLoader, TextureLoader& textureLoader, RenderBus& renderBus);

	// VOID
	void update() override;
	void createEntity(const string& ID);

	// Miscellaneous
	const unordered_map<string, shared_ptr<SpotlightEntity>>& getEntities();
	shared_ptr<SpotlightEntity> getEntity(const string& ID);

	// UNSIGNED INT
	static inline const unsigned int MAX_LIGHT_COUNT = 64;
};